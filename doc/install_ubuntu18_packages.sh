# Must run as root so that we can shutdown backuppc and mount drives 
if [ $(whoami) != "root" ]; then
	echo "Debe ejecutar este guión como «root»."
	echo "Use 'sudo sh instala_paquetes_debian.sh' e introduzca la contraseña cuando se le pida."
	exit 1
fi

echo "Algunos paquetes se encuentran en las áreas «contrib» y «non-free» de la distribución Debian por lo que deben incluirse estas áreas en el archivo «sources.list antes de ejecutar este guión."

# Verificar que el usuario desea continuar
read -p "Continuar (s/n)?" REPLY
if [ $REPLY != "s" ]; then
	echo "Exiting..."
	exit 1
fik

apt-get install cimg-dev cmake g++ gfortran gnuplot libboost-dev libboost-filesystem-dev libboost-python-dev libboost-regex-dev libboost-system-dev libcgal-dev libcgal-qt5-dev libglib2.0-dev libgmp3-dev libgtk2.0-dev libgtkgl2.0-dev libgtkglextmm-x11-1.2-dev libgtkmm-2.4-dev libgtkglext1-dev libgts-bin libgts-dev libmpfr-dev libmysql++-dev libplot-dev libsqlite3-dev libvtk6-dev libX11-dev python-dev python-numpy python-scipy



