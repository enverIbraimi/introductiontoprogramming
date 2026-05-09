import os
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from helpers import login_required

app = Flask(__name__)
db = SQL("sqlite:///eco.db")

# ... (Standard Flask-Session configuration here) ...

@app.route("/")
@login_required
def index():
    # Fetch all reports to display on a map or list
    reports = db.execute("SELECT * FROM reports ORDER BY timestamp DESC")
    return render_template("index.html", reports=reports)

@app.route("/report", methods=["GET", "POST"])
@login_required
def report():
    if request.method == "POST":
        category = request.form.get("category")
        description = request.form.get("description")
        location = request.form.get("location")
        
        if not category or not description or not location:
            return "Must provide all fields", 400
            
        db.execute("INSERT INTO reports (user_id, category, description, location_name) VALUES (?, ?, ?, ?)",
                   session["user_id"], category, description, location)
        
        flash("Observation reported!")
        return redirect("/")
    else:
        return render_template("report.html")