all:
	gcc runner.c -o termshortcutrunner
	gcc poller.c -o termshortcutpoller

install:
	install -o 0 -g 0 -m 700 termshortcutpoller /usr/sbin/termshortcutpoller
	install -o 0 -g 0 -m 700 termshortcutrunner /usr/sbin/termshortcutrunner
	install -o 0 -g 0 -m 600 termshortcut.service /etc/systemd/system/termshortcut.service
	systemctl daemon-reload
	systemctl enable termshortcut
	### DO systemctl start termshortcut TO START TERMSHORTCUTPOLLER

clean:
	rm termshortcutrunner termshortcutpoller
