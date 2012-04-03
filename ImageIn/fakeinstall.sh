if [ "$1" = "uninstall" ];
  then
    for i in *.h *.tpp Algorithm/*.h Algorithm/*.tpp
    do
      rm -v "/usr/local/include/$i"
    done

    rmdir -v "/usr/local/include/Algorithm"

    for i in *.a
    do
      rm -v "/usr/local/lib/$i"
    done
fi

if [ "$1" = "install" ];
  then
    mkdir -v "/usr/local/include/Algorithm"
    for i in *.h *.tpp 
    do
      ln -v -s "$(pwd)/$i" "/usr/local/include/"
    done
    for i in Algorithm/*.h Algorithm/*.tpp
    do
      ln -v -s "$(pwd)/$i" "/usr/local/include/Algorithm"
    done
    for i in *.a
    do
      ln -v -s "$(pwd)/$i" "/usr/local/lib/$i"
    done
fi
