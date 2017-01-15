# Fuzzing test cases for the Qt library

## Building manually

#### Build libfuzzer
... as described at http://libfuzzer.info

####  Build Qt
Qt should be built with address sanitizer options and code coverage information. In addition, it is a good idea to build Qt with the libraries it comes with rather than the system ones (e.g. libjpeg):

```
configure -opensource -confirm-license -platform linux-clang -developer-build \
-debug -no-eglfs -no-widgets -no-compile-examples -nomake examples -nomake tests \
-qt-pcre -qt-zlib -qt-freetype -qt-harfbuzz -qt-xcb -qt-libpng -qt-libjpeg \
-qt-sqlite -sanitize address \
QMAKE_CFLAGS+="-fsanitize-coverage=edge,indirect-calls,8bit-counters" \
QMAKE_CXXFLAGS+="-fsanitize-coverage=edge,indirect-calls,8bit-counters" \
QMAKE_LFLAGS+="-fsanitize-coverage=edge,indirect-calls,8bit-counters" 

make
```

#### Build fuzzing test cases (this repo)
You need to tell qmake explicitly to link against libFuzzer, which was produced in step 1 above:
```
cd /path/to/qt-fuzzing/libFuzzer-testcases
/path/to/qmake "LIBS+=-L/path/to/libFuzzer.a -lFuzzer"
make
```

## Building with Google's OSS-fuzz

TODO

For some reason when updating the fuzzing test cases repository they are not always synced immediately, possibly due to docker caches.
To build the image from scratch, apply the following patch to oss-fuzz:

```
diff --git a/infra/helper.py b/infra/helper.py
index 02af61d..b165014 100755
--- a/infra/helper.py
+++ b/infra/helper.py
@@ -128,7 +128,7 @@ def _build_image(image_name):
       build_args += ['--pull']
   build_args += ['-t', 'ossfuzz/%s' % image_name, dockerfile_dir ]
 
-  command = [ 'docker', 'build' ] + build_args
+  command = [ 'docker', 'build', '--no-cache' ] + build_args
   print('Running:', _get_command_string(command))
 
   try:
```
