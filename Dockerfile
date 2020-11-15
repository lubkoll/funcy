FROM ubuntu:20.04
LABEL description "ci environment for funcy"
ENV CTEST_OUTPUT_ON_FAILURE=1

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y g++-10 gcc-10 ninja-build cmake ccache libdune-common-dev libeigen3-dev python3 python3-pip ruby2.7 clang-10 lcov git

RUN gem install coveralls-lcov
RUN python3 -m pip install conan

RUN useradd -ms /bin/bash funcy
RUN usermod -G sudo funcy
USER funcy

WORKDIR /home/funcy
