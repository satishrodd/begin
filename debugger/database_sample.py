import sqlite3
import readline
#---------------------------------------------
#--All global initialization to be done here--
#---------------------------------------------
db = "example.db"
cmd_tbl = "commands"
inst_tbl = "instruction"
prob_tbl = "problems"
MIN = 1
MAX = 10
def open_db(db_name):
    return sqlite3.connect(str)

def create_tables(conn):
    #-----------TODO--------------#
    #check if the tables are already created, then return
    cursor = conn.cursor()
    # create Commands table
    cursor.execute('''CREATE TABLE {} (id INTEGER PRIMARY KEY AUTOINCREMENT, cmd text)'''.format(cmd_tbl))
    # create Problems table
    cursor.execute('''CREATE TABLE {} (id INTEGER PRIMARY KEY AUTOINCREMENT, prob text)'''.format(prob_tbl))
    # create instructions table
    cursor.execute('''CREATE TABLE {} (id INTEGER PRIMARY KEY AUTOINCREMENT, inst text)'''.format(inst_tbl))


def ask_choice():
    return raw_input("Please choose from above options:")
#-----------------------------------------------
#--ALL command table related code begins here---
#-----------------------------------------------
def insert_cmd (conn, cmd):
    cursor = conn.cursor()
    cursor.execute("INSERT INTO {}(cmd) values (?)".format(cmd_tbl), (cmd,))
    conn.commit()

def show_command_table(conn):
    cursor = conn.cursor()
    i=0;
    for row in cursor.execute("SELECT * FROM {}".format(cmd_tbl)):
        i +=1
        print str(i) + ':' + row[1]

def get_new_cmd(conn):
    cmd = raw_input("enter the complete command: ")
    insert_cmd(conn, str(cmd))

#-----------------------------------------------
#--ALL problem table related code begins here---
#-----------------------------------------------

def insert_prob (conn, prob):
    cursor = conn.cursor()
    cursor.execute("INSERT INTO {}(prob) values (?)".format(prob_tbl), (prob,))
    conn.commit()

def show_problem_table(conn):
    cursor = conn.cursor()
    i=0;
    for row in cursor.execute("SELECT * FROM {}".format(prob_tbl)):
        i +=1
        print str(i) + ":" + row[1] 
    
def get_new_prob(conn):
    cmd = raw_input("enter the issue here: ")
    insert_prob(conn, str(cmd))

#-----------------------------------------------
#--ALL command table related code begins here---
#-----------------------------------------------
def insert_inst (conn, inst):
    cursor = conn.cursor()
    cursor.execute("INSERT INTO {}(inst) values (?)".format(inst_tbl), (inst,))
    conn.commit()

def show_inst_table(conn):
    cursor = conn.cursor()
    i=0;
    for row in cursor.execute("SELECT * FROM {}".format(inst_tbl)):
        i +=1
        print str(i) + ':' + row[1]

def get_new_inst(conn):
    inst = raw_input("enter the complete instruction: ")
    insert_inst(conn, str(inst))

    
#---------------------------------------------
# ----------Handle the choice made------------
#---------------------------------------------
def handle_choice(choice, conn):
    if choice == 1: #Debug issue
        show_problem_table(conn)
        issue = ask_choice()
    elif choice == 2: #New issue
        get_new_prob(conn)
    elif choice == 3: #new command
        get_new_cmd(conn)
    elif choice == 4: #show commands table
        show_command_table(conn)
    elif choice == 5: # new instruction
        get_new_inst(conn)
    elif choice == 6: # show instructions
        show_inst_table(conn)

#-----------------------------------------------
#------------Program begins here----------------
#-----------------------------------------------

# Initialise th connection
conn = sqlite3.connect(db)
c = conn.cursor()
#create_tables(conn)
x = 1
while(x):
    print("1) Debug issue\n" +
          "2) Enter new issue \n" +
          "3) Enter new command\n" +
          "4) Show commands\n" +
          "5) Enter new reason\n" +
          "6) Show reasons\n" +
          "0) Exit")
    try:
        x = int(raw_input())
        if (MIN>x>MAX):
            print("Invalid entry")
            raise Exception

        handle_choice(x, conn)    
    except:
        print("Somethings not right :(,\ncan you try again")
        x = 1

conn.close

