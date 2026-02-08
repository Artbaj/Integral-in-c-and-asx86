#include <unistd.h>  // dla lseek, STDIN_FILENO
#include <fcntl.h>   // dla SEEK_SET
#include <x86intrin.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
//extern uint16_t get_fpu_control_word(void);
//extern uint16_t get_status(void);

//extern void change_precision(void);
#include <stdio.h>
#include <stdint.h>
typedef struct {
    int exponent;
    double coefficient;
}Term;

typedef struct{
    Term *terms;
    int capacity;
    int size;
}Polynomial;


extern double powerOpt(double x,int exp);
extern unsigned long long miernik(void);
void init_poly(Polynomial* p);
int compare_terms(const void *a, const void *b);
void print_poly_array(Polynomial *p); 
void add_term_array(Polynomial *p, int exp, double coeff); 
double poly_eval(Polynomial* p,double x);
double integrate(Polynomial* p,double start,double end,double step);
int main() {
    double startI,endI,step,coefficient;
    int exponent;
    int count = 1;
    Polynomial p;
    init_poly(&p);

    do{
        printf("Provide an coefficient [0 if u are done]\n");
        scanf("%lf",&coefficient);
        if(!coefficient) continue;
        printf("Provide an exponent\n");
        scanf("%d",&exponent);
        add_term_array(&p,exponent,coefficient);
        count++;
       
    }
    while(coefficient);
   

    print_poly_array(&p);
    printf("podaj start koniec i step\n");
    scanf("%lf %lf %lf",&startI,&endI,&step);
   
    FILE *plik = fopen("time.txt","w");
    clock_t start = clock();
    double resoult =  integrate(&p,startI,endI,step);
    clock_t end= clock();
    printf("y = ");
    print_poly_array(&p);
    printf("dla x E <%lf , %lf> Sy(x) = %lf\n",startI,endI,resoult);
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC * 1000; // w ms
    printf("Czas wykonania: %.6f ms\n", time_spent);
    return 0;



}
void init_poly(Polynomial *p) {
    p->size = 0;
    p->capacity = 10;
    p->terms = malloc(p->capacity * sizeof(Term));
}

void add_term_array(Polynomial *p, int exp, double coeff) {
    for (size_t i = 0; i < p->size; i++) {
        
        if (p->terms[i].exponent == exp) {
            p->terms[i].coefficient += coeff;
            return;
        }
    }

    if (p->size >= p->capacity) {
        p->capacity *= 2;
        p->terms = realloc(p->terms, p->capacity * sizeof(Term));
    }

    p->terms[p->size].exponent = exp;
    p->terms[p->size].coefficient = coeff;
    p->size++;
}


int compare_terms(const void *a, const void *b) {
    Term *termA = (Term *)a;
    Term *termB = (Term *)b;
    return (termB->exponent - termA->exponent);

}

void print_poly_array(Polynomial *p) {
    qsort(p->terms, p->size, sizeof(Term), compare_terms);
    for (size_t i = 0; i < p->size; i++) {
        if (p->terms[i].coefficient != 0) // Pomijamy zera
            if(!p->terms[i].exponent) printf("%+.1f", p->terms[i].coefficient);
            else printf("%+.1fx^%d ", p->terms[i].coefficient, p->terms[i].exponent);
    }
    printf("\n");
}

double poly_eval(Polynomial *p,double x){
    double resoult = 0;
    for(size_t i =0;i<p->size;i++){
        resoult+=p->terms[i].coefficient*powerOpt(x,p->terms[i].exponent);
    }
    return resoult;


}
double integrate(Polynomial* p,double start,double end,double step){
        double area =0;
        for(double i=start;i<end-step;i+=step){
            area += poly_eval(p,i)*step;
        }
        return area;
    };

