from flask import render_template, url_for, flash, redirect, request, abort
from application import app, db, bcrypt
from application.forms import RegistrationForm, LoginForm, TeaForm, RecommendForm
from application.models import User, Tea
from flask_login import login_user, current_user, logout_user, login_required
from sqlalchemy import func, or_
import datetime


@app.route('/')
def index():
    if current_user.is_authenticated:
        return redirect(url_for('inventory'))
    else:
        return redirect(url_for('login'))

@app.route('/inventory')
@login_required
def inventory():
    page = request.args.get('page', 1, type=int)
    teas = Tea.query.filter_by(userID=current_user.get_id()).order_by(Tea.rating.desc()).paginate(page=page,per_page=25)
    return render_template('inventory.html', title='Inventory', teas=teas)


@app.route('/tea/add', methods=['GET', 'POST'])
@login_required
def add():
    form = TeaForm()
    if form.validate_on_submit():
        tea = Tea(name=form.teaName.data, type=form.teaType.data, userID=current_user.get_id(),
                  rating=form.teaRating.data, season=", ".join(form.teaSeason.data), tags=", ".join(form.teaTags.data))
        db.session.add(tea)
        db.session.commit()
        flash(f'{form.teaName.data} has been added!', 'success')
        return redirect(url_for('inventory'))
    return render_template('add.html', title='Add New Tea', form=form, legend='Add Your Tea')


@app.route("/register", methods=['GET', 'POST'])
def register():
    if current_user.is_authenticated:
        return redirect(url_for('inventory'))
    form = RegistrationForm()
    if form.validate_on_submit():
        hashedPW = bcrypt.generate_password_hash(form.password.data).decode('utf-8')
        user = User(username=form.username.data, email=form.email.data, password=hashedPW)
        db.session.add(user)
        db.session.commit()
        flash(f'Account created for {form.username.data}!', 'success')
        return redirect(url_for('login'))
    return render_template('register.html', title='Register', form=form)


@app.route("/login", methods=['GET', 'POST'])
def login():
    if current_user.is_authenticated:
        return redirect(url_for('index'))
    form = LoginForm()
    if form.validate_on_submit():
        user = User.query.filter_by(email=form.email.data).first()
        if user and bcrypt.check_password_hash(user.password, form.password.data):
            login_user(user, remember=form.remember.data)
            next_page = request.args.get('next')
            return redirect(next_page) if next_page else redirect(url_for('index'))
        else:
            flash('Login Unsuccessful. Please check email and password', 'danger')
    return render_template('login.html', title='Login', form=form)


@app.route("/logout")
def logout():
    logout_user()
    return render_template('index.html')


@app.route("/account")
@login_required
def account():
    return render_template('account.html', title='Account')


@app.route("/tea/<int:tea_id>/edit", methods=['GET', 'POST'])
@login_required
def tea(tea_id):
    tea = Tea.query.get_or_404(tea_id)
    if tea.userID != current_user.id:
        abort(403)
    form = TeaForm()
    if form.validate_on_submit():
        tea.name=form.teaName.data
        tea.type=form.teaType.data
        tea.rating=int(form.teaRating.data)
        tea.season=", ".join(form.teaSeason.data)
        tea.tags=", ".join(form.teaTags.data)
        db.session.commit()
        flash(f'{form.teaName.data} has been updated!', 'success')
        return redirect(url_for('inventory'))
    elif request.method == 'GET':
        form.teaName.data = tea.name
        form.teaType.data = tea.type
        form.teaRating.data = str(tea.rating)
        form.teaSeason.data = tea.season
        form.teaTags.data = tea.tags
        edit = True
    return render_template('add.html', title='Edit Tea', form=form, legend='Edit Your Tea', edit=edit)

@app.route("/tea/<int:tea_id>/delete", methods=['POST'])
@login_required
def delete_tea(tea_id):
    tea = Tea.query.get_or_404(tea_id)
    if tea.userID != current_user.id:
        abort(403)
    db.session.delete(tea)
    db.session.commit()
    flash('Your tea has been deleted!', 'success')
    return redirect(url_for('inventory'))


@app.route('/tea/recommend', methods=['GET', 'POST'])
@login_required
def recommend():
    form = RecommendForm()
    if form.validate_on_submit():
        return redirect(url_for('recommend'))
    teas = Tea.query.filter_by(userID=current_user.get_id())
    today = datetime.date.today()
    if today.month == 3 or today.month == 4 or today.month == 5:
        teas = Tea.query.filter_by(userID=current_user.get_id()).filter(or_(Tea.season.contains('Spring'),
                                                                            Tea.season.contains('Anytime')))
    elif today.month == 6 or today.month == 7 or today.month == 8:
        teas = Tea.query.filter_by(userID=current_user.get_id()).filter(or_(Tea.season.contains('Summer'),
                                                                            Tea.season.contains('Anytime')))
    elif today.month == 9 or today.month == 10 or today.month == 11:
        teas = Tea.query.filter_by(userID=current_user.get_id()).filter(or_(Tea.season.contains('Fall'),
                                                                            Tea.season.contains('Anytime')))
    elif today.month == 12 or today.month == 1 or today.month == 2:
        teas = Tea.query.filter_by(userID=current_user.get_id()).filter(or_(Tea.season.contains('Winter'),
                                                                            Tea.season.contains('Anytime')))
    else:
        teas = Tea.query.filter_by(userID=current_user.get_id()).filter_by(season='Anytime')
    randomTea = teas.order_by(func.random()).first()
    return render_template('recommend.html', title='Recommend Me A Tea', form=form, legend='Recommend Me A Tea',
                           randomTea=randomTea)
