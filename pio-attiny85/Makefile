SERIAL_DEVICE		= /dev/ttyACM*

all:
	platformio -f -c vim run

upload: monitor-close
	platformio -f -c vim run --target upload

clean:
	platformio -f -c vim run --target clean

update:
	platformio -f -c vim update

find-serial:
	ls -1 $(SERIAL_DEVICE)
	$(eval USBTTY=$(shell ls -1 $(SERIAL_DEVICE) | head -n1 ))

monitor: find-serial
	tools/monitor.sh open $(USBTTY) $(MONITOR_BAUD)

monitor-close:
	tools/monitor.sh close

monitor-loop: find-monitor-baud find-serial
	-tools/monitor.sh loop $(USBTTY) $(MONITOR_BAUD)

monitor-notify-done:
	tools/monitor.sh notify-done
