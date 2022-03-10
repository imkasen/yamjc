FROM alpine:latest AS builder

RUN sed -i "s/dl-cdn.alpinelinux.org/mirrors.aliyun.com/g" /etc/apk/repositories \
    && apk update \
    && apk add --no-cache build-base \
    flex \
    flex-dev \
    bison \
    cmake \
    && rm -rf /var/cache/apk/*

WORKDIR /home/

COPY . /home/

RUN mkdir build \
    && cd build \
    && cmake .. \
    && make


FROM alpine:latest AS prod

RUN sed -i "s/dl-cdn.alpinelinux.org/mirrors.aliyun.com/g" /etc/apk/repositories \
    && apk update \
    && apk add --no-cache bash \
    graphviz \
    && rm -rf /var/cache/apk/*

WORKDIR /home/

COPY --from=builder /home/build/compiler .
COPY resource/tests/ /home/tests/
COPY graph.sh /home/
