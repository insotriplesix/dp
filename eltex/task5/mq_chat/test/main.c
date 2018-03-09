#include "chat.h"

int main(int argc, char *argv[])
{
	key = ftok(argv[0], 'm');

	if ((qid = open_queue(key)) == ERR) {
		perror("opa");
		exit(1);
	}

	struct msg m_snd, m_rcv;

	m_snd.type = 1;
	strcpy(m_snd.text, "Hello, World!");

	if (fork() == 0) {
		if ((send_message(qid, &m_snd)) == ERR) {
			perror("pa");
			exit(1);
		}
	} else {
		if ((recv_message(qid, 2, &m_rcv)) == ERR) {
			perror("a");
			exit(1);
		}

		printf("%ld -- %s\n", m_rcv.type, m_rcv.text);
	}

	return 0;
}
