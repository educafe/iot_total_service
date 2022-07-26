import mysql.connector
import time


mydb = mysql.connector.connect(
  host="localhost",
  user="root",
  passwd="root",
  database="mydb1",
  port="3306"
)

mycursor = mydb.cursor()

sql = "INSERT INTO dht11 (temperature_humidity, created) VALUES (%s, %s)"
val = ("Temp:26C, Humi:14%", time.localtime(time.time()))
mycursor.execute(sql, val)

mydb.commit()

print(mycursor.rowcount, "record inserted.")