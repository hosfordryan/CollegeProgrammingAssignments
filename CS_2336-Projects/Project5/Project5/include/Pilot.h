#ifndef PILOT_H
#define PILOT_H


class Pilot
{
    public:
		Pilot(string inN){name = inN; lengthOfPath = 0; validPath = true;}; //Constructor
		string getName(){return name;}; //Return name
		int getLength(){return lengthOfPath;};  //Return length
		bool getValid(){return validPath;};     //Return if it valid

		setName(string in){name = in;};     //Set name
		setLengthOfPath(int in){lengthOfPath = in;};    //Let length
		setValid(bool in){validPath = in;};     //Set valid

		incrementLength(int in){lengthOfPath += in;};   //Add to the length

		bool operator < (const Pilot& other) const  //Overload the comparison for sorting
		{
			return (lengthOfPath < other.lengthOfPath);
		}

	private:
		string name;
		int lengthOfPath;
		bool validPath;
};

#endif // PILOT_H

