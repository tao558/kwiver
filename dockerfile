# Install KWIVER to /opt/kitware/kwiver
# Use latest Fletch as base image (Ubuntu 18.04)
ARG BASE_IMAGE=kitware/fletch:latest

FROM ${BASE_IMAGE}
ARG PY_MAJOR_VERSION=3
ARG ENABLE_CUDA=OFF
ARG KWIVER_INSTALL=/opt/kitware/kwiver

# Conditonal installtion of six
RUN if [ "$PY_MAJOR_VERSION" = "2" ]; then \
      pip install six; \
    else \
      pip3 install six; \
    fi
#
# Build KWIVER
#
COPY . /kwiver
RUN cd /kwiver \
  && mkdir build \
  && cd build \
  && cmake ../ -DCMAKE_BUILD_TYPE=Release \
    -Dfletch_DIR:PATH=/opt/kitware/fletch/share/cmake \
    -DCMAKE_INSTALL_PREFIX=${KWIVER_INSTALL} \
    -DKWIVER_ENABLE_ARROWS=ON \
    -DKWIVER_ENABLE_C_BINDINGS=ON \
    -DKWIVER_ENABLE_BURNOUT:BOOL=OFF \
    -DKWIVER_ENABLE_CERES:BOOL=OFF \
    -DKWIVER_ENABLE_CUDA:BOOL=${ENABLE_CUDA} \
    -DKWIVER_ENABLE_C_BINDINGS:BOOL=ON \
    -DKWIVER_ENABLE_DARKNET:BOOL=ON \
    -DKWIVER_ENABLE_DLL_WARNINGS:BOOL=OFF \
    -DKWIVER_ENABLE_DOCS:BOOL=OFF \
    -DKWIVER_ENABLE_EXAMPLES:BOOL=ON \
    -DKWIVER_ENABLE_EXTRAS:BOOL=ON \
    -DKWIVER_ENABLE_KPF:BOOL=ON \
    -DKWIVER_ENABLE_LOG4CPLUS:BOOL=ON \
    -DKWIVER_ENABLE_LOG4CXX:BOOL=OFF \
    -DKWIVER_ENABLE_MATLAB:BOOL=OFF \
    -DKWIVER_ENABLE_OPENCV:BOOL=ON \
    -DKWIVER_ENABLE_PROCESSES:BOOL=ON \
    -DKWIVER_ENABLE_PROJ:BOOL=ON \
    -DKWIVER_ENABLE_CERES=ON \
    -DKWIVER_ENABLE_EXTRAS=ON \
    -DKWIVER_ENABLE_LOG4CPLUS=ON \
    -DKWIVER_ENABLE_OPENCV=ON \
    -DKWIVER_ENABLE_PROCESSES=ON \
    -DKWIVER_ENABLE_PROJ=ON \
    -DKWIVER_ENABLE_PYTHON=ON \
    -DKWIVER_ENABLE_SPROKIT=ON \
    -DKWIVER_ENABLE_TESTS=ON \
    -DKWIVER_ENABLE_TOOLS=ON \
    -DKWIVER_ENABLE_TRACK_ORACLE:BOOL=ON \
    -DKWIVER_ENABLE_UUID:BOOL=OFF \
    -DKWIVER_ENABLE_VISCL:BOOL=OFF \
    -DKWIVER_ENABLE_VXL:BOOL=ON \
    -DKWIVER_ENABLE_SERIALIZE_PROTOBUF:BOOL=ON \
    -DKWIVER_ENABLE_SERIALIZE_JSON:BOOL=ON \
    -DKWIVER_ENABLE_ZeroMQ:BOOL=ON \
    -DKWIVER_INSTALL_SET_UP_SCRIPT:BOOL=ON \
    -DKWIVER_ENABLE_VXL=ON \
    -DKWIVER_PYTHON_MAJOR_VERSION=${PY_MAJOR_VERSION} \
    -DKWIVER_USE_BUILD_TREE=OFF \
  && make -j$(nproc) -k \
  && make install \
  && rm -rf /kwiver

RUN echo "source /opt/kitware/kwiver/setup_KWIVER.sh">>/etc/bash.bashrc

CMD [ "bash" ]
