import sqlite3
cmd_db = "commands.db"
inst_db = "instruction.db"

conn = sqlite3.connect('example.db')
c = conn.cursor()
#c.execute('''CREATE TABLE abc (id number, name text)''')
c.execute("INSERT INTO abc values (1,'satish')")
conn.commit()
c.execute("SELECT * FROM abc")
print c.fetchall()
conn.close
