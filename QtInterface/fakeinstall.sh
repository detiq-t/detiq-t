if [ "$1" = "uninstall" ];
  then
    for i in *.h Services/*.h Widgets/ImageWidgets/*.h Widgets/NavBar/*.h Utilities/*.h
    do
      rm -v "/usr/local/include/$i"
    done

    rmdir -v "/usr/local/include/Services"
    rmdir -v "/usr/local/include/Widgets/ImageWidgets"
    rmdir -v "/usr/local/include/Widgets/NavBar"
    rmdir -v "/usr/local/include/Widgets"
    rmdir -v "/usr/local/include/Utilities"

    for i in *.so*
    do
      rm -v "/usr/local/lib/$i"
    done
fi

if [ "$1" = "install" ];
  then
    mkdir -v "/usr/local/include/Services"
    mkdir -v "/usr/local/include/Widgets"
    mkdir -v "/usr/local/include/Utilities"
    mkdir -v "/usr/local/include/Widgets/ImageWidgets"
    mkdir -v "/usr/local/include/Widgets/NavBar"

    for i in *.h
    do
      ln -v -s "$(pwd)/$i" "/usr/local/include"
    done
    for i in Services/*.h
    do
      ln -v -s "$(pwd)/$i" "/usr/local/include/Services"
    done
    for i in Widgets/ImageWidgets/*.h 
    do
      ln -v -s "$(pwd)/$i" "/usr/local/include/Widgets/ImageWidgets"
    done
    for i in Widgets/NavBar/*.h
    do
      ln -v -s "$(pwd)/$i" "/usr/local/include/Widgets/NavBar"
    done
    for i in Utilities/*.h 
    do
      ln -v -s "$(pwd)/$i" "/usr/local/include/Utilities"
    done

    for i in *.so*
    do
      ln -v -s "$(pwd)/$i" "/usr/local/lib"
    done
fi
