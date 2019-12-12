#include <fstream>
#include <iostream>
#include "dynamic_bitset.hpp"

std::string mask_to_string(auto &variables)
{
	std::string temp;
	for(std::size_t itr = 0; itr < variables.size(); ++itr)
	{
		temp += "x";
		temp += std::to_string(itr);
		temp += ": ";
		temp += std::to_string(variables.at(itr));
		temp += ", ";
	}

	return temp;
}

//this version does not bother removing clauses, instead it checks if the expression is valid every time a configuration has been generated
void print_sat_solutions(bit::Bitset <unsigned char> variables, auto &and_masks, auto &xor_masks, int k, int threshold)
{
	//threshold = variables.size()
	if(k == threshold)
	{
		//check if false is fine
		for(std::size_t clause_itr = 0; clause_itr < and_masks.size(); ++clause_itr)
		{
			auto var = variables;
			//bits are already set, xor them to switch negatives, then and them to get rid of missing bits
			if(((var ^= xor_masks[clause_itr]) &= and_masks[clause_itr]).none())	//if current config is 0 => clause is false, we can stop
				return;
		}
		//managed to skip past all the ifs => all of the clauses are true, print the config
		std::cout << mask_to_string(variables) << std::endl;

		return;
	}
	


	//we reach the variable with 0
	print_sat_solutions(variables, and_masks, xor_masks, k + 1, threshold);	//move to the next variable

	//after returning set it to 1
	variables.set(k);
	print_sat_solutions(variables, and_masks, xor_masks, k + 1, threshold);	//move to the next variable, this time with the bit set

	//after returning set the bit to 0 and go back
	variables.reset(k);
	return;

}


void print_sat_solutions_opt(bit::Bitset <unsigned char> variables, auto and_masks, auto xor_masks, int k, int threshold)
{
	//threshold = variables.size()
	if(k == threshold)
	{
		//check if there are no clauses left (meaning all of them became true somewhere along the tree)
		if(and_masks.size() == 0)
			std::cout << mask_to_string(variables) << std::endl;

		return;
	}

	//we will set up new clauses and work with them in the next calls
	std::vector <bit::Bitset <unsigned char>> and_masks_unset;
	std::vector <bit::Bitset <unsigned char>> xor_masks_unset;
	std::vector <bit::Bitset <unsigned char>> and_masks_set;
	std::vector <bit::Bitset <unsigned char>> xor_masks_set;

	//order of clauses is not relevant
	//push clauses that are false if the k-th variable is NOT set
	for(std::size_t clause_itr = 0; clause_itr < and_masks.size(); ++clause_itr)
	{
		auto var_unset = variables;
		if(((var_unset ^= xor_masks[clause_itr]) &= and_masks[clause_itr]).none())	//if no bits are set => clause is false
		{
			//clause is false for unset variable, push it
			and_masks_unset.push_back(and_masks[clause_itr]);
			xor_masks_unset.push_back(xor_masks[clause_itr]);
		}

		auto var_set = variables;
		var_set.set(k);
		if(((var_set ^= xor_masks[clause_itr]) &= and_masks[clause_itr]).none())	//if no bits are set => clause is false
		{
			//clause is false for set variable, push it
			and_masks_set.push_back(and_masks[clause_itr]);
			xor_masks_set.push_back(xor_masks[clause_itr]);
		}

	}

	//we reach the variable with 0
	print_sat_solutions_opt(variables, and_masks_unset, xor_masks_unset, k + 1, threshold);	//move to the next variable

	//after returning set it to 1
	variables.set(k);
	print_sat_solutions_opt(variables, and_masks_set, xor_masks_set, k + 1, threshold);	//move to the next variable, this time with the bit set

	//after returning set the bit to 0 and go back
	variables.reset(k);
	return;
}

int main(int argc, char **argv)
{
	std::ifstream in(argv[1]);

	int k;
	in >> k;

	bit::Bitset <unsigned char> variables(k, false);		//so were gonna have a bitset for the values of our variables, we will backtrack on this checking every possible combination
	std::vector <bit::Bitset <unsigned char>> xor_masks;
	std::vector <bit::Bitset <unsigned char>> and_masks;	//we will have a+1 masks, where a = number of ands in our expression, we will use the mask to XOR out unneeded bits as well as swap not bits

	//xor_mask[i] will be true IFF i-th bit is !not, we can then xor with the current chunk to reverse needed bits
	//and_mask[i] will be true IFF i-th bit actually is present in the current chunk

	std::string temp;
	and_masks.push_back(bit::Bitset <unsigned char> (k, false));	//we pushing the first mask first
	xor_masks.push_back(bit::Bitset <unsigned char> (k, false));
	while(in >> temp)
	{
		if(temp == "and")
		{
			//create a new mask
			and_masks.push_back(bit::Bitset <unsigned char> (k, false));
			xor_masks.push_back(bit::Bitset <unsigned char> (k, false));
		}
		else if(temp != "or")
		{
			//we have a variable
			int variable_index;
			if(temp[0] == '!')
			{
				variable_index = std::stoi(temp.substr(1, temp.size())); 	//remove ! and convert to int
				xor_masks.back().set(variable_index);						//variable is negative => set the bit in the xor mask as well
			}
			else
				variable_index = std::stoi(temp);

			and_masks.back().set(variable_index);							//setting the vars bit to 1
		}
	}

	for(auto itr : and_masks)
		std::cout << itr << ' ';
	std::cout << std::endl;
	for(auto itr : xor_masks)
		std::cout << itr << ' ';
	std::cout << std::endl;

	//masks seem fine

	print_sat_solutions_opt(variables, and_masks, xor_masks, 0, k);


	return 0;
}