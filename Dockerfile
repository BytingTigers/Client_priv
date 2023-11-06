####################
# Base-Build
####################

FROM ubuntu:16.04 AS base

ENV DEBIAN_FRONTEND=noninteractive

# Install build tools
RUN apt-get update && apt-get install -y \
    gcc \
    gcc-multilib \
    libc6 \
    libc6-dev \
    net-tools \
    git \
    autoconf \
    automake \
    libtool \
    pkg-config \
    make \
    checkinstall \
    build-essential \
    git \
    zlib1g-dev \
    wget

####################
# Build-Client
####################

FROM base as build-client

ARG CACHEBUST=1
RUN git clone https://github.com/BytingTigers/Client_priv.git /client
WORKDIR /client
RUN make clean
RUN make CFLAGS='-z execstack -fno-stack-protector -z norelro -g -O0'

####################
# Execution
####################

FROM build-client as execution

RUN chmod +x /client/client

CMD ["/client/client"]
