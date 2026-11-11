import sys
from pathlib import Path
import time
from datetime import datetime
import serial
from serial.tools import list_ports
VENDOR_ID = 0x2E8A
PRODUCT_ID = 0x000A
TASK = "1.3.4"
PROJECT = "133-led-button-usb"
LOG_NAME = "device-1-3-4.log"
COMMANDS = ["e", "d", "e", "e", "d", "x"]
ANSWER_TIMEOUT_S = 1
def find_board():
    for port in list_ports.comports():
        if port.vid == VENDOR_ID and port.pid == PRODUCT_ID:
            return port
    return None
def talk(board):
    exchange = []
    with serial.Serial(board.device, timeout=ANSWER_TIMEOUT_S) as port:
        time.sleep(0.2)
        port.reset_input_buffer()
        started = time.monotonic()
        for command in COMMANDS:
            port.write(command.encode("ascii"))
            exchange.append((time.monotonic() - started, "-->", command))
            answer = port.readline().decode("ascii", "replace").strip()
            exchange.append((time.monotonic() - started, "<--", answer))
            time.sleep(0.5)
    return exchange
def write_log(board, exchange):
    with open(Path(__file__).resolve().parent / LOG_NAME, "w", encoding="utf-8") as log:
        log.write("задание: " + TASK + "\n")
        log.write("проект: " + PROJECT + "\n")
        log.write("устройство: %04x:%04x\n" % (board.vid, board.pid))
        log.write("серийный номер: " + str(board.serial_number) + "\n")
        log.write("порт: " + board.device + "\n")
        log.write("начало: " + datetime.now().isoformat(timespec="seconds") + "\n")
        for moment, direction, text in exchange:
            log.write("%8.3f %s %s\n" % (moment, direction, text))
        log.write("итог: отправлено команд %d\n" % len(COMMANDS))
board = find_board()
if board is None:
    sys.exit(1)
else:
    exchange = talk(board)
    write_log(board, exchange)