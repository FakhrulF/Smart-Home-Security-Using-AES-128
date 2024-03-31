#import telebot
import flask
import time
import json
import codecs
from flask import render_template, request
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives import padding
import base64
import binascii
from base64 import b64encode, b64decode
from supabase_py import create_client
import time
import psutil

cpu_usage = 0
memory_usage = 0
decrypt_memory_usage = 0
decrypt_cpu_usage = 0
decryptTime = 0
encryptTime = 0
key = 'ThisIsASecretKey'
encrypted_data = ""
decrypted_data = ""
def encrypt_message(key, message):
    global encryptTime, memory_usage, cpu_usage, total_memory
    print("Sebelum encrypt:")
    start_time = time.time_ns()
    print(start_time)
    key_bytes = key.encode('utf-8')
    message_bytes = message.encode('utf-8')
    padder = padding.PKCS7(128).padder()
    padded_data = padder.update(message_bytes) + padder.finalize()
    cipher = Cipher(algorithms.AES(key_bytes), modes.ECB(), backend=default_backend())
    encryptor = cipher.encryptor()
    encrypted_data = encryptor.update(padded_data) + encryptor.finalize()
    encrypted_base64 = base64.b64encode(encrypted_data).decode('utf-8')
    print("Sesudah encrypt:") 
    end_time = time.time_ns()
    print(end_time)
    encryptTime = end_time-start_time
    print(f"{encryptTime} ns")
    memory_usage = psutil.virtual_memory().percent
    total_memory = mem. total
    total_memory_gb = total_memory / (1024 ** 3)
    cpu_usage = psutil.cpu_percent()
    return encrypted_base64

def debug_decrypt_message(key, encrypted_base64):
    global decryptTime, decrypt_memory_usage, decrypt_cpu_usage, decrypt_total_memory
    print("Waktu decrypt sebelum:")
    dec_start_time = time.time_ns()
    print(dec_start_time)
    key_bytes = key.encode('utf-8')
    encrypted_data = base64.b64decode(encrypted_base64)
    cipher = Cipher(algorithms.AES(key_bytes), modes.ECB(), backend=default_backend())
    decryptor = cipher.decryptor()
    decrypted_padded_data = decryptor.update(encrypted_data) + decryptor.finalize()
    unpadder = padding.PKCS7(128).unpadder()
    decrypted_data = unpadder.update(decrypted_padded_data) + unpadder.finalize()
    decrypted_message = decrypted_data.decode('utf-8')
    dec_end_time = time.time_ns()
    print("Waktu decrypt sesudah:")
    print(dec_end_time)
    decryptTime = dec_end_time-dec_start_time
    print(f"DecryptTime:{decryptTime} ns")
    decrypt_memory_usage = psutil.virtual_memory().percent
    decrypt_total_memory = mem.total
    total_memory_gb = total_memory / (1024 ** 3)
    decrypt_cpu_usage = psutil.cpu_percent()
    return decrypted_message

def decrypt_message(key, encrypted_base64):
    key_bytes = key.encode('utf-8')
    encrypted_data = base64.b64decode(encrypted_base64)
    cipher = Cipher(algorithms.AES(key_bytes), modes.ECB(), backend=default_backend())
    decryptor = cipher.decryptor()
    decrypted_padded_data = decryptor.update(encrypted_data) + decryptor.finalize()
    unpadder = padding.PKCS7(128).unpadder()
    decrypted_data = unpadder.update(decrypted_padded_data) + unpadder.finalize()
    decrypted_message = decrypted_data.decode('utf-8')
    return decrypted_message
    

topic = ""
payload = ""
aes_payload = ""
data_payload = ""
app = flask.Flask(__name__)
from flask_mqtt import Mqtt
app.config['MQTT_BROKER_URL'] = 'localhost'
app.config['MQTT_BROKER_PORT'] = 1883
app.config['MQTT_REFRESH_TIME'] = 1.0  # refresh time in seconds
mqtt = Mqtt(app)
@mqtt.on_connect()
def handle_connect(client, userdata, flags, rc):
    mqtt.subscribe('topic/smarthome/testing/aes')
    mqtt.subscribe('topic/smarthome/testing/data')
@mqtt.on_message()
def handle_message(client, userdata, message):
    global topic, payload, aes_payload, data_payload
    topic = message.topic
    payload = message.payload.decode()
    print('Received message on topic {}: {}'.format(message.topic, message.payload.decode()))
    if topic == 'topic/smarthome/testing/aes':
        aes_payload = payload
    

        
        encrypted_message = encrypt_message(key, aes_payload)
        
        debug_decrypt_message(key,encrypted_message)

        
        client.publish('topic/smarthome/testing/encrypt', str(encrypted_message))
        new_record = {'uid': encrypted_message}
        respopse = supaClient.from_('keyLog').insert(new_record).execute()
        if 'error' in respopse:
            print('Operation failed for adding keylog:', respopse['error'])
        else:
            print('Operation successful adding keylog')
    elif topic == 'topic/smarthome/testing/data':
        data_payload = payload
        data = json.loads(data_payload)
        global humi, tempf, tempc, encrypted_data
        if data:
            humi = data['humi']
            tempf = data['tempf']
            tempc = data['tempc']
            new_record = {'temp_f': tempf, 'temp_c': tempc, 'humi' : humi}
            respopse = supaClient.from_('temperature').insert(new_record).execute()
            if 'error' in respopse:
                print('Operation failed for adding general data:', respopse['error'])
            else:
                print('Operation successful for adding general data')
#MQTT
@app.route('/')
def koordinat():
    table_name = 'temperature'
    tempData = supaClient.table(table_name).select().execute()
    keyLog = 'keyLog'
    encrypted_data_list = supaClient.table(keyLog).select().execute()
    decrypted_data_list = []
    logDecrypt = []
    for entry in encrypted_data_list['data']:
        encrypted_uid = entry['uid']
        decrypted_data = decrypt_message(key,encrypted_uid)
        decrypted_data_list.append(decrypted_data)
    print(logDecrypt)
    
    for i, entry in enumerate(encrypted_data_list['data']):
        entry['decrypted_data'] = decrypted_data_list[i]
    dispp = render_template('Beranda.html', title='Beranda Smarthome Fakhrul', tempData=tempData, keyLogData=encrypted_data_list, encryptTime=encryptTime, logDecrypt = logDecrypt, mqttTopic=topic, mqttPayload=aes_payload, mqttDataLoad=data_payload, decryptTime=decryptTime, cpu_usage = cpu_usage, memory_usage = memory_usage, decrypt_cpu_usage = decrypt_cpu_usage, decrypt_memory_usage = decrypt_memory_usage)
    return dispp
if __name__ == '__main__':
    app.run(host='0.0.0.0', port=80, debug=True)
