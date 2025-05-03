# Dockerfile
FROM ubuntu:22.04

# Install dependencies
RUN apt-get update && \
    apt-get install -y g++ build-essential && \
    apt-get clean

# Set working directory inside container
WORKDIR /workspace

# Default command: bash
CMD ["/bin/bash"]
