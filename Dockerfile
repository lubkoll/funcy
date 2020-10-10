FROM ubuntu:20.04
LABEL description "ci environment for funcy"
ENV CTEST_OUTPUT_ON_FAILURE=1
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y g++-10 gcc-10 ninja-build cmake ccache libeigen3-dev python3 python3-pip ruby2.7
RUN python3 -m pip install conan
RUN gem install coveralls-lcov

