#!/bin/bash

echo -e "\033[036msortList\033[0m"
echo -e "\033[036mWordlist Management Tool\033[0m"
echo ""
if [ "$(id -u)" != "0" ]; then
	   echo "This script must be run as root!" 1>&2
	      exit 1
      fi

echo "Checking dependancies"
apt-get -qq update -q # Get the latest package lists
apt-get -qq install g++ -y




echo "Installing to /usr/share/sortlist"
if [ -d "/usr/share/sortlist" ]; then
	while true; do
		read -p "Install directory already found, are you sure you want to overwrite? (y/n)" yn
		case $yn in
			[Yy]* ) g++ sortList.cpp input.cpp -std=c++11 -o /usr/share/sortlist/sortlist; break;;
			[Nn]* ) exit;;
			 * ) echo "Please answer y or n.";;
		 esac
	done
else
	mkdir /usr/share/sortlist
	g++ sortList.cpp input.cpp -std=c++11 -o /usr/share/sortlist/sortlist;
fi

while true; do
	read -p "Would you like to add a symlink to sortList?(y/n) (y if unsure)"yn
	case $yn in
		[Yy]* ) ln -s "/usr/share/sortlist/sortlist"  /usr/local/bin/sortlist;
		       echo "Use the command 'sortlist' to run the program"; break;;
		[Nn]* ) exit;;
		* ) echo "Please answer y or n.";;
	esac
done
echo "Install completed"
