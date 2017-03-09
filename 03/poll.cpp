#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

class CQuestion {
	string text;

public:
	CQuestion(const string & text) : text(text) {}

	void print(ostream & out) const {
		out << text;
	}
};

class COption {
	static int maxId;

	string text;
	int votes;
	int id;

public:
	COption (const string & text, int votes = 0) :
	text(text),
	votes(votes),
	id(++maxId) {}

	int getId() const {
		return id;
	}

	int getVotes() const {
		return votes;
	}

	void addVote() {
		++votes;
	}

	void print(ostream & out, int totalVotes) const {
		out << id << ") " << text;

		if (votes > 0) {
			out << setfill(' ') << setw(50 - text.length());
			out << '(' << votes << "x - " << (votes*100)/totalVotes << "%)";
		}
	}
};

int COption::maxId = 0;

class CPoll {
	CQuestion question;
	vector<COption> options;
	int totalVotes;

	void addVote(int id) {
		for (auto it = options.begin(); it != options.end(); ++it) {
			if (it->getId() == id) {
				++totalVotes;
				it->addVote();
				break;
			}
		}
	}

	static void sortByVotes(vector<COption> & a) {
		sort(a.begin(), a.end(), [](const COption & a, const COption & b) {
			return b.getVotes() < a.getVotes();
		});
	}

public:
	CPoll(const string & question) :
	question(question),
	totalVotes(0) {}

	CPoll & addOption(const COption & option) {
		options.push_back(option);
		return *this;
	}

	CPoll & addOption(const string & text) {
		return addOption(COption(text));
	}

	bool hasId(int id) {
		for (auto it = options.begin(); it != options.end(); ++it) {
			if (it->getId() == id) return true;
		}

		return false;
	}

	bool addVote(const vector<int> & ids) {
		for (auto it = ids.begin(); it != ids.end(); ++it) {
			if ( ! hasId(*it) ) return false;
		}

		for (auto it = ids.begin(); it != ids.end(); ++it) {
			addVote(*it);
		}

		return true;
	}

	void print(ostream & out) const {
		vector<COption> tmp(options);
		sortByVotes(tmp);

		question.print(out);

		if(totalVotes > 0) {
			out << " (" << totalVotes << "x)";
		}

		out << "\n\n";

		for (auto it = tmp.begin(); it != tmp.end(); ++it) {
			it->print(out, totalVotes);
			out << endl;
		}
	}
};

int main() {
	CPoll poll("What is your favourite meal?");

	poll.addOption(COption("Strawberry"))
		.addOption("Blueberry")
		.addOption("Youghurt")
		.addOption("Biscuit")
		.addOption("Whale steak");

	vector<int> votes;

	poll.print(cout);

	votes.push_back(1);
	votes.push_back(1);
	votes.push_back(1);
	votes.push_back(2);
	votes.push_back(3);
	votes.push_back(3);
	votes.push_back(3);
	votes.push_back(3);
	votes.push_back(5);

	poll.addVote(votes);

	poll.print(cout);

	return 0;
}
