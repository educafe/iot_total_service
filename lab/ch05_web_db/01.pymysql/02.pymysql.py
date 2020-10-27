import pymysql
import time
 
conn = pymysql.connect(host='localhost', user='root', password='root',
                       db='mydb1', charset='utf8')
 
curs = conn.cursor()
sql = """insert into dht11(temperature_humidity,created) values (%s,%s)"""
curs.execute(sql, ("Temp:26C, Humi:18%", time.localtime(time.time())))
conn.commit()
 
conn.close()