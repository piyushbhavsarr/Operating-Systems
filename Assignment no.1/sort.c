#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>

void Bubble_sort(int arr[30],int n)
{
	int i,j,temp;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n-1;j++)
		{
			if(arr[j]>arr[j+1])
			{
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
}
void insertion_sort(int arr[30],int n)
{
	 int i ,j ,temp;
	for(i=0;i<n;i++)
	{
		temp=arr[i];
		j=i-1;
		while(j>=0 && temp<=arr[j])
		{
			arr[j+1]=arr[j];
			j=j-1;
		}
		arr[j+1]=temp;
		
	}
}
void fork1()
{
	int arr[25],arr1[25],n,i,status;
	printf("Enter the number of values in array :");
	scanf("%d",&n);
	printf("Enter the array element :");
	for(i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	int pid=fork();
	if(pid==0)
	{
		sleep(10);
		printf("Child process \n");
		printf("Child process id = %d\n",getpid());
		insertion_sort(arr,n);
      		printf("Element sorted using insertion sort :");
		printf("\n");
		for(i=0;i<n;i++)
		{
			printf("%d\t",arr[i]);
		}
		printf("\b");
		printf("\n Parent Process id = %d\n",getppid());
		system("ps -x");
		printf("\n\n\n");
	}
	else
	{
		printf("Parent process \n");
		printf("parent process id = %d \n",getppid());
		Bubble_sort(arr,n);
		printf("Element sorted using bubble sort:\n");
		printf("\n");
		for(i=0;i<n;i++)
		{
			printf("%d\t",arr[i]);
			
		}
		printf("\n\n\n");
	}
}
int main()

{
	fork1();
	return 0;
}

/*OUTPUT
ty60@pc21:~/Desktop/OS$ cc sort.c
ty60@pc21:~/Desktop/OS$ ./a.out
Enter the number of values in array :5
Enter the array element :5 2 1 6 9
Parent process 
parent process id = 7062 
Element sorted using bubble sort:

1	2	5	6	9	


ty60@pc21:~/Desktop/OS$ 
Child process 
Child process id = 8700
Element sorted using insertion sort :
1	2	5	6	9	

 Parent Process id = 1164
    PID TTY      STAT   TIME COMMAND
   1164 ?        Ss     0:00 /lib/systemd/systemd --user
   1165 ?        S      0:00 (sd-pam)
   1179 ?        S<sl   0:00 /usr/bin/pipewire
   1180 ?        S<sl   0:00 /usr/bin/pulseaudio --daemonize=no --log-target=jou
   1182 ?        SNsl   0:02 /usr/libexec/tracker-miner-fs
   1186 ?        Ss     0:02 /usr/bin/dbus-daemon --session --address=systemd: -
   1202 ?        S<l    0:00 /usr/bin/pipewire-media-session
   1203 ?        Ssl    0:00 /usr/libexec/gvfsd
   1208 ?        Sl     0:00 /usr/libexec/gvfsd-fuse /run/user/30060/gvfs -f
   1217 ?        Ssl    0:00 /usr/libexec/gvfs-udisks2-volume-monitor
   1222 ?        Ssl    0:00 /usr/libexec/gvfs-mtp-volume-monitor
   1226 ?        Ssl    0:00 /usr/libexec/gvfs-afc-volume-monitor
   1228 ?        Sl     0:00 /usr/bin/gnome-keyring-daemon --daemonize --login
   1235 ?        Ssl    0:00 /usr/libexec/gvfs-gphoto2-volume-monitor
   1239 ?        Ssl    0:00 /usr/libexec/gvfs-goa-volume-monitor
   1243 ?        Sl     0:00 /usr/libexec/goa-daemon
   1251 ?        Sl     0:00 /usr/libexec/goa-identity-service
   1260 tty2     Ssl+   0:00 /usr/libexec/gdm-wayland-session /usr/bin/gnome-ses
   1263 tty2     Sl+    0:00 /usr/libexec/gnome-session-binary --systemd
   1303 ?        Ssl    0:00 /usr/libexec/gnome-session-ctl --monitor
   1304 ?        Ss     0:00 ssh-agent -D -a /run/user/30060/openssh_agent
   1307 ?        Ssl    0:00 /usr/libexec/gnome-session-binary --systemd-service
   1326 ?        Sl     0:00 /usr/libexec/at-spi-bus-launcher --launch-immediate
   1333 ?        Ssl    2:10 /usr/bin/gnome-shell
   1338 ?        S      0:00 /usr/bin/dbus-daemon --config-file=/usr/share/defau
   1362 ?        Sl     0:00 /usr/bin/Xwayland :0 -rootless -noreset -accessx -c
   1369 ?        Ssl    0:00 /usr/libexec/xdg-permission-store
   1374 ?        Sl     0:00 /usr/libexec/gnome-shell-calendar-server
   1384 ?        Ssl    0:00 /usr/libexec/evolution-source-registry
   1390 ?        Ssl    0:00 /usr/libexec/gvfsd-metadata
   1397 ?        Sl     0:00 /usr/bin/gjs /usr/share/gnome-shell/org.gnome.Shell
   1399 ?        Sl     0:00 /usr/libexec/at-spi2-registryd --use-gnome-session
   1408 ?        Ssl    0:00 /usr/libexec/gsd-a11y-settings
   1409 ?        Ssl    0:00 /usr/libexec/gsd-color
   1410 ?        Ssl    0:00 /usr/libexec/gsd-datetime
   1412 ?        Ssl    0:00 /usr/libexec/gsd-housekeeping
   1415 ?        Ssl    0:00 /usr/libexec/gsd-keyboard
   1417 ?        Ssl    0:00 /usr/libexec/gsd-media-keys
   1418 ?        Ssl    0:00 /usr/libexec/gsd-power
   1419 ?        Ssl    0:00 /usr/libexec/gsd-print-notifications
   1420 ?        Ssl    0:00 /usr/libexec/gsd-rfkill
   1422 ?        Ssl    0:00 /usr/libexec/gsd-screensaver-proxy
   1423 ?        Ssl    0:00 /usr/libexec/gsd-sharing
   1428 ?        Ssl    0:00 /usr/libexec/gsd-smartcard
   1430 ?        Ssl    0:00 /usr/libexec/gsd-sound
   1433 ?        Ssl    0:00 /usr/libexec/gsd-usb-protection
   1434 ?        Ssl    0:00 /usr/libexec/gsd-wacom
   1445 ?        Sl     0:00 /usr/libexec/evolution-data-server/evolution-alarm-
   1467 ?        Sl     0:04 /usr/bin/gnome-software --gapplication-service
   1471 ?        Sl     0:00 /usr/libexec/gsd-disk-utility-notify
   1504 ?        Sl     0:00 /usr/libexec/gsd-printer
   1562 ?        Ssl    0:00 /usr/libexec/evolution-calendar-factory
   1607 ?        Sl     0:18 ibus-daemon --panel disable -r --xim
   1610 ?        Ssl    0:01 /usr/libexec/gsd-xsettings
   1622 ?        Sl     0:00 /usr/libexec/dconf-service
   1632 ?        Ssl    0:00 /usr/libexec/evolution-addressbook-factory
   1655 ?        Sl     0:00 /usr/libexec/ibus-memconf
   1656 ?        Sl     0:03 /usr/libexec/ibus-extension-gtk3
   1665 ?        Sl     0:00 /usr/libexec/ibus-x11 --kill-daemon
   1670 ?        Sl     0:00 /usr/libexec/ibus-portal
   1722 ?        Sl     0:06 /usr/libexec/ibus-engine-simple
   2243 ?        Sl     0:00 /usr/libexec/gvfsd-trash --spawner :1.4 /org/gtk/gv
   2300 ?        Sl     0:00 /usr/libexec/gvfsd-burn --spawner :1.4 /org/gtk/gvf
   2309 ?        Sl     1:50 /usr/bin/gedit --gapplication-service
   2758 ?        Sl     0:07 /usr/bin/nautilus --gapplication-service
   3095 ?        Sl     0:00 /usr/libexec/gvfsd-network --spawner :1.4 /org/gtk/
   3112 ?        Sl     0:00 /usr/libexec/gvfsd-dnssd --spawner :1.4 /org/gtk/gv
   7057 ?        Ssl    0:06 /usr/libexec/gnome-terminal-server
   7062 pts/0    Ss+    0:00 bash
   8615 ?        Ssl    0:00 /usr/libexec/tracker-store
   8700 pts/0    S      0:00 ./a.out
   8708 pts/0    S      0:00 sh -c ps -x
   8709 pts/0    R      0:00 ps -x
*/
