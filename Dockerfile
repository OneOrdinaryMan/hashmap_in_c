FROM gcc:latest as runner
WORKDIR /usr/src/myapp
COPY . .
CMD ["/bin/bash", "-c", "make run"]
