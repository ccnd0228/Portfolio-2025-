from datetime import datetime, timedelta
import turtle
import tkinter as tk
from tkinter import messagebox

def calculate_water_charge(previous_reading, current_reading):
    consumption = current_reading - previous_reading
    if consumption < 0:
        raise ValueError("Current reading must be greater than or equal to previous reading.")
    
    if consumption <= 10:
        return consumption * 10
    else:
        return (10 * 10) + ((consumption - 10) * 15)

def draw_border(width, height):
    turtle.speed(10)
    turtle.penup()
    turtle.color("White")
    turtle.goto(-width/2, height/2)
    turtle.pendown()
    for _ in range(2):
        turtle.forward(width)
        turtle.right(90)
        turtle.forward(height)
        turtle.right(90)

def draw_header():
    turtle.penup()
    title = "WATER BILL"
    turtle.goto(-230, 200)
    turtle.pendown()
    turtle.write(title, font=("Times New Roman", 24, "bold"))
    
    turtle.penup()
    turtle.goto(-230, 170)
    turtle.pendown()
    turtle.write("Thank you for choosing GIRLPALCO.", font=("Times", 16, "italic"))
    
    turtle.penup()
    turtle.goto(-230, 100)
    turtle.pendown()
    turtle.write("Please view your bill summary below.", font=("Times", 14, "italic"))

def draw_section(label, value, y_position):
    turtle.penup()
    turtle.goto(-230, y_position)
    turtle.pendown()
    turtle.write(f"{label}: {value}", font=("Times New Roman", 16, "normal"))

def show_receipt(data):
    turtle.setup(500, 300)
    screen = turtle.Screen()
    screen.bgcolor("Black")

    width = 500
    height = 600

    draw_border(width, height)
    draw_header()

    for i, (label, value) in enumerate(data.items()):
        draw_section(label, value, 10 - (i * 30))

    turtle.done()

def calculate_and_show_receipt():
    try:
        name = name_entry.get()
        account_number = account_entry.get()
        reading_date = datetime.strptime(reading_date_entry.get(), "%Y-%m-%d").date()
        connection_type = connection_entry.get().strip()
        previous_reading = float(previous_reading_entry.get())
        current_reading = float(current_reading_entry.get())
        arrears = float(arrears_entry.get())
        amount_paid = float(amount_paid_entry.get())
        payment_date = datetime.strptime(payment_date_entry.get(), "%Y-%m-%d").date()

        water_charge = calculate_water_charge(previous_reading, current_reading)
        vat = water_charge * 0.12
        total_amount_before_due_date = water_charge + vat
        due_date = reading_date + timedelta(days=30)

        amount_due = total_amount_before_due_date + arrears
        penalty_amount = 0

        if payment_date > due_date:
            penalty_amount = 50
            amount_due += penalty_amount

        change = amount_paid - amount_due

        receipt_data = {
            "Reading Date": str(reading_date),
            "Connection Type": connection_type,
            "Water Charge": f"{water_charge:.2f} pesos",
            "VAT (12%)": f"{vat:.2f} pesos",
            "Total Before Due Date": f"{total_amount_before_due_date:.2f} pesos",
            "Arrears": f"{arrears:.2f} pesos",
            "Penalty Amount": f"{penalty_amount:.2f} pesos",
            "Total Amount Due After Penalty": f"{amount_due:.2f} pesos",
            "Change": f"{change:.2f} pesos",
            "Account Number": account_number,
            "Customer Name": name
        }

        messagebox.showinfo("Loading", "Receipt will show up in a few seconds...")
        show_receipt(receipt_data)

    except ValueError as e:
        messagebox.showerror("Input Error", str(e))
    except Exception as e:
        messagebox.showerror("Error", "An unexpected error occurred: " + str(e))

def create_gui():
    global name_entry, account_entry, reading_date_entry, connection_entry
    global previous_reading_entry, current_reading_entry, arrears_entry, amount_paid_entry, payment_date_entry

    root = tk.Tk()
    root.title("Water Bill Calculator")

    tk.Label(root, text="Customer Name:").grid(row=0, column=0)
    name_entry = tk.Entry(root)
    name_entry.grid(row=0, column=1)

    tk.Label(root, text="Account Number:").grid(row=1, column=0)
    account_entry = tk.Entry(root)
    account_entry.grid(row=1, column=1)

    tk.Label(root, text="Reading Date (YYYY-MM-DD):").grid(row=2, column=0)
    reading_date_entry = tk.Entry(root)
    reading_date_entry.grid(row=2, column=1)

    tk.Label(root, text="Connection Type (Residential/Commercial):").grid(row=3, column=0)
    connection_entry = tk.Entry(root)
    connection_entry.grid(row=3, column=1)

    tk.Label(root, text="Previous Reading:").grid(row=4, column=0)
    previous_reading_entry = tk.Entry(root)
    previous_reading_entry.grid(row=4, column=1)

    tk.Label(root, text="Current Reading:").grid(row=5, column=0)
    current_reading_entry = tk.Entry(root)
    current_reading_entry.grid(row=5, column=1)

    tk.Label(root, text="Arrears:").grid(row=6, column=0)
    arrears_entry = tk.Entry(root)
    arrears_entry.grid(row=6, column=1)

    tk.Label(root, text="Amount Paid:").grid(row=7, column=0)
    amount_paid_entry = tk.Entry(root)
    amount_paid_entry.grid(row=7, column=1)

    tk.Label(root, text="Payment Date (YYYY-MM-DD):").grid(row=8, column=0)
    payment_date_entry = tk.Entry(root)
    payment_date_entry.grid(row=8, column=1)

    tk.Button(root, text="Calculate and Show Receipt", command=calculate_and_show_receipt).grid(row=9, columnspan=2)

    root.mainloop()

if __name__ == "__main__":
    create_gui()
