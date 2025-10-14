[Mozc - a Japanese Input Method Editor designed for multi-platform](https://github.com/google/mozc)
===================================

Copyright 2010-2025 Google LLC

Mozc is a Japanese Input Method Editor (IME) designed for multi-platform such as
Android, macOS, Chromium OS, Linux and Windows.

Mozc is not an officially supported Google product.

Build Status
------------

| Linux | Windows | macOS | Android lib |
|:-----:|:-------:|:-----:|:-----------:|
| [![Linux](https://github.com/google/mozc/actions/workflows/linux.yaml/badge.svg)](https://github.com/google/mozc/actions/workflows/linux.yaml) | [![Windows](https://github.com/google/mozc/actions/workflows/windows.yaml/badge.svg)](https://github.com/google/mozc/actions/workflows/windows.yaml) | [![macOS](https://github.com/google/mozc/actions/workflows/macos.yaml/badge.svg)](https://github.com/google/mozc/actions/workflows/macos.yaml) | [![Android lib](https://github.com/google/mozc/actions/workflows/android.yaml/badge.svg)](https://github.com/google/mozc/actions/workflows/android.yaml) |

What's Mozc?
------------
For historical reasons, the project name *Mozc* has two different meanings:

1. Internal code name of Google Japanese Input that is still commonly used
   inside Google.
2. Project name to release a subset of Google Japanese Input in the form of
   source code under OSS license without any warranty nor user support.

In this repository, *Mozc* means the second definition unless otherwise noted.

Build Instructions
------------------

* [How to build Mozc for Android](docs/build_mozc_for_android.md): for Android library (`libmozc.so`)
* [How to build Mozc for Linux](docs/build_mozc_for_linux.md): for Linux desktop
* [How to build Mozc for macOS](docs/build_mozc_in_osx.md): for macOS build
* [How to build Mozc for Windows](docs/build_mozc_in_windows.md): for Windows

How is Mozc developed?
---------------------

You may find how Mozc is developed is a bit obscure and different from other
open source projects that use GitHub as the true upstream. It is most likely
bacause the code here is an open source counterpart of a subset of the Google
internal monorepo.

There are two types of code change flows around this repository:

 1. New commits in the Google internal monorepo will be published into this
    reporitory with necessary code transformations.
 2. New commits in this open source repository through pull-request will be
    imported into the Google internal monorepo with necessary code
    transformations.

For this to happen, the Mozc team internally uses a tool called
[Copybara](https://github.com/google/copybara) like other Google-developed open
source projects such as:

 * [Abseil](https://github.com/abseil/abseil-cpp)
 * [Bazel](https://github.com/bazelbuild/bazel)
 * [Protocol Buffers](https://github.com/protocolbuffers/protobuf/)

Release Plan
------------

This project only offers a single development branch.

License
-------

All Mozc code written by Google is released under
[The BSD 3-Clause License](http://opensource.org/licenses/BSD-3-Clause).
For third party code under [src/third_party](src/third_party) directory,
see each sub directory to find the copyright notice.  Note also that
outside [src/third_party](src/third_party) following directories contain
third party code.

### [src/data/dictionary_oss/](src/data/dictionary_oss)
Mixed.
See [src/data/dictionary_oss/README.txt](src/data/dictionary_oss/README.txt)

### [src/data/test/dictionary/](src/data/test/dictionary)
The same as [src/data/dictionary_oss/](src/data/dictionary_oss).
See [src/data/dictionary_oss/README.txt](src/data/dictionary_oss/README.txt)

### [src/data/test/stress_test/](src/data/test/stress_test)
Public Domain.  See the comment in
[src/data/test/stress_test/sentences.txt](src/data/test/stress_test/sentences.txt)
