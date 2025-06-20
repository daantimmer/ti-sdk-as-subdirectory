FROM ghcr.io/philips-software/amp-devcontainer-cpp:v6.0.2@sha256:36afaaa5ba4bc4e9bb471012db9733c26a210e315ddb33600f73bb9532b02a25

#checkov:skip=CKV_DOCKER_3: this container needs to run as root

ARG DEBIAN_FRONTEND=noninteractive
ARG TI_CLANG_VERSION=3.2.2.LTS

HEALTHCHECK NONE

SHELL ["/bin/bash", "-o", "pipefail", "-c"]

# Install the base system with all tool dependencies
COPY .devcontainer/apt-requirements-base.json /tmp/apt-requirements-base.json
# hadolint ignore=DL3008
RUN apt-get update && apt-get install -y --no-install-recommends jq \
    && jq -r 'to_entries | .[] | .key + "=" + .value' /tmp/apt-requirements-base.json | xargs apt-get install -y --no-install-recommends \
    && rm /tmp/apt-requirements-base.json \
    && rm -rf /var/lib/apt/lists/*

RUN CORRECTED_ARCH="$(uname -m | sed s/x86_64/x64/ | sed s/aarch64/arm64/)" \
    && python3 -m pip install jsonschema==4.23.0 --no-cache-dir --break-system-packages \
    && wget -q "https://dr-download.ti.com/software-development/ide-configuration-compiler-or-debugger/MD-ayxs93eZNN/${TI_CLANG_VERSION}/ti_cgt_armllvm_${TI_CLANG_VERSION}_linux-${CORRECTED_ARCH}_installer.bin" -P /tmp/ \
    && chmod a+x "/tmp/ti_cgt_armllvm_${TI_CLANG_VERSION}_linux-${CORRECTED_ARCH}_installer.bin" \
    && "/tmp/ti_cgt_armllvm_${TI_CLANG_VERSION}_linux-${CORRECTED_ARCH}_installer.bin" --prefix /opt/ \
    # libtinfo.so.5 is not available through apt-get, but libtinfo.so.6 also works.
    # libtinfo.so.5 is a required dependency for version ti-clang 3.2.2
    && ln -sf "/usr/lib/$(uname -m)-linux-gnu/libtinfo.so.6" "/usr/lib/$(uname -m)-linux-gnu/libtinfo.so.5"

ENV PATH="$PATH:/opt/ti-cgt-armllvm_${TI_CLANG_VERSION}/bin/"
