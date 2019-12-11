import cs50
import csv

from flask import Flask, jsonify, redirect, render_template, request

# Configure application
app = Flask(__name__)

# Reload templates when they are changed
app.config["TEMPLATES_AUTO_RELOAD"] = True


@app.after_request
def after_request(response):
    """Disable caching"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET"])
def get_index():
    return redirect("/form")


@app.route("/form", methods=["GET"])
def get_form():
    return render_template("form.html")


@app.route("/form", methods=["GET", "POST"])
def post_form():
    # Check for valid input incase javascript is disabled
    if not request.form.get("name"):
        return render_template("error.html", message="You must provide your tea's name!")
    elif not request.form.get("tea-type"):
        return render_template("error.html", message="You must provide your tea's type!")
    elif not request.form.get("season"):
        return render_template("error.html", message="You must provide your tea's season!")
    else:
        # Go to sheets page if valid

        # Set up the string for tags
        tags = ", ".join(request.form.getlist("tags"))

        # Open the CSV in append mode & add a line to the end
        with open("survey.csv", "a+") as surveyFile:
            addSurvey = csv.writer(surveyFile)
            addSurvey.writerow([request.form.get("name"), request.form.get("tea-type"), request.form.get("season"), tags])

        # Open the sheet page
        with open("survey.csv", "r") as surveyFile:
            csvReader = csv.reader(surveyFile)

            for teas in csvReader:
                return render_template("sheet.html", survey=csvReader)


@app.route("/sheet", methods=["GET"])
def get_sheet():
    # Open survey.csv
    with open("survey.csv", "r") as surveyFile:
        csvReader = csv.reader(surveyFile)

        for teas in csvReader:
            return render_template("sheet.html", survey=csvReader)
