from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, SubmitField, BooleanField, SelectField, SelectMultipleField
from wtforms.validators import DataRequired, Length, Email, EqualTo, ValidationError
from application.models import User
from wtforms.widgets import ListWidget, CheckboxInput


class MultiCheckboxField(SelectMultipleField):
    widget = ListWidget(prefix_label=False)
    option_widget = CheckboxInput()


class RegistrationForm(FlaskForm):
    username = StringField('Username',
                           validators=[DataRequired(), Length(min=4, max=20)])
    email = StringField('E-mail',
                        validators=[DataRequired(), Email()])
    password = PasswordField('Password', validators=[DataRequired()])
    confirm_password = PasswordField('Confirm Password',
                                     validators=[DataRequired(), EqualTo('password')])
    submit = SubmitField('Register')

    def validateusername(self, username):
        user = User.query.filter_by(username=username.data).first()
        if user:
            raise ValidationError('That username is already taken.')

    def validateemail(self, email):
        email = User.query.filter_by(email=email.data).first()
        if email:
            raise ValidationError('That email is already is use.')


class LoginForm(FlaskForm):
    email = StringField('Email',
                        validators=[DataRequired(), Email()])
    password = PasswordField('Password', validators=[DataRequired()])
    remember = BooleanField('Remember Me?')
    submit = SubmitField('Login')


class TeaForm(FlaskForm):
    teaName = StringField('Tea Name', validators=[DataRequired()])
    teaType = SelectField('Tea Type', validators=[DataRequired()],
                          choices=[('Black Tea', 'Black Tea'), ('White Tea', 'White Tea'), ('Green Tea', 'Green Tea'),
                                   ('Oolong Tea', 'Oolong Tea'), ('Rooibos Tea', 'Rooibos Tea'),
                                   ('Herbal Tea', 'Herbal Tea'), ('Matcha', 'Matcha'), ('Puerh Tea', 'Pu\'erh Tea'),
                                   ('Mate Tea', 'Maté Tea')])
    teaRating = SelectField('Rating',
                            choices=[('', ''), ('1', '1'), ('2', '2'), ('3', '3'), ('4', '4'), ('5', '5')])
    teaSeason = MultiCheckboxField('Best Season',
                            choices=[('Anytime', 'Anytime'), ('Winter', 'Winter'), ('Fall', 'Fall'),
                                     ('Spring', 'Spring'), ('Summer', 'Summer')])
    teaTags = MultiCheckboxField('Tags',
                                  choices=[('Christmas', 'Christmas'), ('Under the Weather', 'Under the Weather'),
                                           ('Decaf', 'Decaf'), ('Relaxing', 'Relaxing'), ('Chai', 'Chai'),
                                           ('Fruity', 'Fruity'), ('Floral', 'Floral'), ('Spicy', 'Spicy'),
                                           ('Smoky', 'Smoky')])
    submit = SubmitField('Log Your Tea')


class RecommendForm(FlaskForm):
    submit = SubmitField('Recommend Another')
