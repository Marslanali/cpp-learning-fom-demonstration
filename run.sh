NAME="cpp-learning-from-demonstration"

docker build -t $NAME . && \
	docker run -it $NAME /bin/bash
