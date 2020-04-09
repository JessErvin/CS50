import os
from flask import Flask
from flask_sqlalchemy import SQLAlchemy
from flask_bcrypt import Bcrypt
from flask_login import LoginManager

app = Flask(__name__)
app.config['SECRET_KEY'] = os.environ.get('SECRETKEY')
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///site.db'
db = SQLAlchemy(app)
bcrypt = Bcrypt(app)
loginManager = LoginManager(app)

# Login view is equal to the function name of the route we use to login.
# This will return us to the the login screen if we try to access a page that requires a login
loginManager.login_view = 'login'
loginManager.login_message_category = 'info'

from application import routes