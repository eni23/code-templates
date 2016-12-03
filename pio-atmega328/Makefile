SERIAL_DEVICE		= /dev/ttyUSB*

.PHONY: all inotify-watch-upload monitor-loop find-monitor-baud find-serial

all:
	platformio -f -c vim run

upload: monitor-close
	platformio -f -c vim run --target upload --verbose

upload-reopen-monitor: all upload monitor-notify-done

clean:
	platformio -f -c vim run --target clean --verbose

program:
	platformio -f -c vim run --target program --verbose

update: --verbose
	platformio -f -c vim update

find-serial:
	ls -1 $(SERIAL_DEVICE)
	$(eval USBTTY=$(shell ls -1 $(SERIAL_DEVICE) 2>/dev/null | head -n1 ))

find-monitor-baud:
	$(eval MONITOR_BAUD=$(shell tools/config-value.sh SERIAL_BAUD ))

monitor: find-monitor-baud find-serial
	tools/monitor.sh open $(USBTTY) $(MONITOR_BAUD)

monitor-close:
	tools/monitor.sh close

monitor-loop: find-monitor-baud find-serial 
	-tools/monitor.sh loop $(USBTTY) $(MONITOR_BAUD)

monitor-notify-done:
	tools/monitor.sh notify-done
