/*
 * polynomial.cpp
 *
 *  Created on: Nov 14, 2018
 *      Author: s263huan
 */
#include <iostream>
#include <cmath>
#include "Polynomial.h"

#ifndef MARMOSET_TESTING
int main();
#endif

#ifndef MARMOSET_TESTING
int main(){
	poly_t poly{nullptr,0};
	poly_t q_poly{nullptr,0};
	return 0;
}
#endif

void init_poly( poly_t &p, double const init_coeffs[],
    unsigned int const init_degree ){
	if (p.a_coeffs != nullptr)
	{
		delete []p.a_coeffs;
		p.a_coeffs = nullptr;
		p.degree = 0;
	}
	else
	{
		p.degree = init_degree;
		p.a_coeffs = new double [init_degree + 1];
		for (std::size_t i = 0; i <= init_degree; i++)
		{
			p.a_coeffs[i] = init_coeffs[i];
		}
	}
}
void destroy_poly( poly_t &p ){
	delete []p.a_coeffs;
	p.a_coeffs = nullptr;
	p.degree = 0;
}
unsigned int poly_degree( poly_t const &p ){
	if (p.a_coeffs == nullptr){
		throw 0;
	}else{
		return p.degree;
	}
}
double poly_coeff ( poly_t const &p, unsigned int n ){
	if (p.a_coeffs == nullptr){
		throw 0;
	}else{
		if (n <= p.degree){
			return p.a_coeffs[n];
		}else{
			return 0.0;
		}
	}
}
double poly_val( poly_t const &p, double x ){
	if (p.a_coeffs == nullptr){
			throw 0;
		}else{
			double value{0.0};
			for(int k = p.degree; k>0; --k){
				value = value *x + p.a_coeffs[k];
			}
		return value *x + p.a_coeffs[0];
}
}
void poly_add( poly_t &p, poly_t const &q ){
	if (p.a_coeffs == nullptr || q.a_coeffs == nullptr){
				throw 0;
	}
	else{
		poly_t add{nullptr,0};
		if(p.degree > q.degree)
		{
			add.degree = p.degree;
			add.a_coeffs=new double[add.degree+1]{0};
			//variable for for loop
			std::size_t i = 0;
			for(i=0;i<q.degree+1;i++)
			{
				add.a_coeffs[i] = q.a_coeffs[i];
			}
			for(i=0;i<q.degree+1;i++){
				p.a_coeffs[i] = add.a_coeffs[i] + p.a_coeffs[i];
			}
			delete[] add.a_coeffs;
		}
		else if(p.degree == q.degree)
		{
			add.degree = p.degree;
			while(q.a_coeffs[add.degree] + p.a_coeffs[add.degree] == 0){
				add.degree--;
			}
			//for for loop
			std::size_t i = 0;
			add.a_coeffs = new double[add.degree+1]{0};
			for(i=0; i<add.degree+1;i++){
				add.a_coeffs[i] = q.a_coeffs[i] + p.a_coeffs[i];
			}
			destroy_poly(p);
			p.degree = add.degree;
			p.a_coeffs= new double [p.degree+1];
			for(i=0; i<p.degree+1; i++){
				p.a_coeffs[i] = add.a_coeffs[i];
			}
			destroy_poly(add);
		}
		else
		{
			add.degree = q.degree;
			add.a_coeffs = new double[add.degree+1]{0};
			std::size_t i=0;
			for (i=0; i<p.degree+1;i++){
				add.a_coeffs[i]=p.a_coeffs[i];
			}
			destroy_poly(p);
			p.degree = add.degree;
			p.a_coeffs= new double [p.degree+1];
			for(i=0; i<p.degree+1; i++){
				p.a_coeffs[i] = add.a_coeffs[i]+q.a_coeffs[i];
			}
			destroy_poly(add);
		}

	}
}
void poly_subtract( poly_t &p, poly_t const &q ){
	if (p.a_coeffs == nullptr || q.a_coeffs == nullptr){
			throw 0;
		}
		else{
			poly_t subtract{nullptr,0};
			if(p.degree > q.degree)
			{
				subtract.degree = p.degree;
				subtract.a_coeffs=new double[subtract.degree+1]{0};
				//variable for for loop
				std::size_t i = 0;
				for(i=0;i<q.degree+1;i++)
				{
					subtract.a_coeffs[i] = q.a_coeffs[i];
				}
				for(i=0;i<p.degree+1;i++){
					p.a_coeffs[i] = p.a_coeffs[i] - subtract.a_coeffs[i];
				}
				delete[] subtract.a_coeffs;
			}
			else if(p.degree == q.degree)
			{
				subtract.degree = p.degree;
				while(q.a_coeffs[subtract.degree] - p.a_coeffs[subtract.degree] == 0){
					subtract.degree--;
				}
				//for for loop
				std::size_t i = 0;
				subtract.a_coeffs = new double[subtract.degree+1]{0};
				for(i=0; i<subtract.degree+1;i++){
					subtract.a_coeffs[i] = q.a_coeffs[i] - p.a_coeffs[i];
				}
				destroy_poly(p);
				p.degree = subtract.degree;
				p.a_coeffs= new double [p.degree+1]{0};
				for(i=0; i<p.degree+1; i++){
					p.a_coeffs[i] = subtract.a_coeffs[i];
				}
				destroy_poly(subtract);
			}
			else
			{
				subtract.degree = q.degree;
				subtract.a_coeffs = new double[subtract.degree+1]{0};
				std::size_t i=0;
				for (i=0; i<p.degree+1;i++){
					subtract.a_coeffs[i]=p.a_coeffs[i];
				}
				destroy_poly(p);
				p.degree = subtract.degree;
				p.a_coeffs= new double [p.degree+1];
				for(i=0; i<p.degree+1; i++){
					p.a_coeffs[i] = subtract.a_coeffs[i]-q.a_coeffs[i];
				}
				delete[] subtract.a_coeffs;
			}

		}
	}
void poly_multiply( poly_t &p, poly_t const &q ){
			if (p.a_coeffs == nullptr || q.a_coeffs == nullptr){
						throw 0;
			}else{
				if ((p.degree==0 && p.a_coeffs[0] == 0) || (q.degree==0 && q.a_coeffs[0]==0))
				{
					destroy_poly(p);
					p.degree=0;
					p.a_coeffs = new double[1]{0};
				}else{
				poly_t multiply{nullptr,0};
			    multiply.degree = p.degree + q.degree;
				multiply.a_coeffs = new double [multiply.degree+1]{0};
				for (int m=0; m<=p.degree; m++){
					for (int n=0; n<=q.degree;n++){
						multiply.a_coeffs[m+n] += p.a_coeffs[m]*q.a_coeffs[n];
					}
				}
				destroy_poly(p);
				p.degree = multiply.degree;
				p.a_coeffs = new double [multiply.degree + 1]{0};
				for (int k=0; k<=multiply.degree; k++){
					p.a_coeffs[k] = multiply.a_coeffs[k];
				}
				destroy_poly(multiply);
	}
			}
}
double poly_divide( poly_t &p, double r ){
	if (p.a_coeffs == nullptr){
		throw 0;
	}else if(p.degree == 0){
		return p.a_coeffs[0];
	}else{
		int k=0;
		double div[p.degree];
		for (int k = p.degree-1; k>=0; k--){
			if (k != p.degree-1){
				div[k] = p.a_coeffs[k+1] + r*div[k+1];
			}else{
				div[k] = p.a_coeffs[p.degree];
			}
		}
		k++;
		int remainder =  p.a_coeffs[k] + r*div[k];
		init_poly(p,div,p.degree-1);
		return remainder;
	}
}
void poly_diff( poly_t &p ){
	double diff[p.degree];
	if (p.a_coeffs == nullptr){
			throw 0;
		}else{
			for (int k=0; k<p.degree; k++){
				diff[k]=p.a_coeffs[k+1]*(k+1);
			}
		}
		init_poly(p, diff, p.degree-1);
}
double poly_approx_int( poly_t const &p, double a, double b, unsigned int n ){
	double h = (b-a)/n;
	double sum_of_area = 0.0;
	if (p.a_coeffs == nullptr){
				throw 0;
	}else{
		for (int i = 0; i<=n; i++){
			if (i ==0 || i==n){
				sum_of_area = h/2*(sum_of_area + poly_val(p, a + i*h));
			}else{
				sum_of_area= h/2*(sum_of_area + 2*poly_val(p, a + i*h));
			}
		}
		return sum_of_area;
	}

}



