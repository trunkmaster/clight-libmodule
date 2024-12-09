git checkout 5.0.2
if [ -d .build ];then
    cd .build
    xargs rm < install_manifest.txt
    cd ..
fi
rm -rf .build
mkdir .build
cd .build
cmake .. \
    -DCMAKE_C_COMPILER=clang \
    -DCMAKE_CXX_COMPILER=clang++ \
    -DCMAKE_INSTALL_PREFIX=/usr/NextSpace
