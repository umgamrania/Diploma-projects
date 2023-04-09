import json
from flask import Flask , render_template , url_for, request, flash, redirect
data = {}

with open("data.json","r+") as file:
    data = json.load(file)

app = Flask(__name__)

@app.route("/", methods=['GET', 'POST'])
@app.route("/login", methods=['GET', 'POST'])
def login_page():
    if request.method == 'POST':
        x = data.get(request.form.get('username'))
        actual_password = data.get(request.form.get('username'), -1)

        if actual_password == -1:
            return render_template("login.html", wrong=True, msg='User does not exist')
        elif request.form.get('password') != actual_password:
            return render_template("login.html", wrong=True, msg='Wrong Password')
        else:
            return render_template("dashboard.html")
        
    return render_template("login.html", wrong=False)

@app.route("/create", methods=['GET', 'POST'])
def create_page():
    if request.method == 'POST':
        if data.get(request.form.get('username'), -1) == -1:
            data[request.form.get('username')] = request.form.get('password')
            print(data)
            with open("data.json","w") as file:
                json.dump(data,file,indent=4)
            return redirect(url_for('login_page'))
        else:
            return render_template('create.html', error=True)
    return render_template("create.html", error=False)

app.run(debug = True)