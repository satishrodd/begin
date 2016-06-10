import sqlite3
import readline
db = "example.db"
cmd_tbl = "commands"
inst_tbl = "instruction"
prob_tbl = "problems"
MIN = 1
MAX = 3
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

def insert_cmd (conn, cmd):
    cursor = conn.cursor()
    cursor.execute("INSERT INTO {}(cmd) values (?)".format(cmd_tbl), (cmd,))
    conn.commit()

def show_command_table(conn):
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM {}".format(cmd_tbl))
    print cursor.fetchall()
    
def get_new_cmd(conn):
    cmd = raw_input("enter the complete command: ")
    insert_cmd(conn, str(cmd))

def insert_prob (conn, prob):
    cursor = conn.cursor()
    cursor.execute("INSERT INTO {}(prob) values (?)".format(prob_tbl), (prob,))
    conn.commit()

def show_problem_table(conn):
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM {}".format(prob_tbl))
    print cursor.fetchall()
    
def get_new_prob(conn):
    cmd = raw_input("enter the issue here: ")
    insert_prob(conn, str(cmd))
    
conn = sqlite3.connect(db)
c = conn.cursor()
#create_tables(conn)
#get_new_cmd(conn)
show_command_table(conn)
#get_new_prob(conn)
show_problem_table(conn)
x = 1
'''
while(x):
    print("1) Debug issue\n" +
          "2) Enter new issue \n" +
          "3) Enter new command\n" +
          "0) Exit")
    try:
        x = int(raw_input())
        if (MIN>x>MAX):
            print("Invalid entry")
            raise Exception
            
    except:
        print("Invalid Entry")
        x = 1
'''
conn.close
