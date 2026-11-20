// Original Apple M2 C++17 inference benchmark.
// AI-assisted source: timed blocks of an untrained synthetic neural network.
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

static uint32_t seed_value = 123456789u;
float pseudo_random() { seed_value = 1664525u * seed_value + 1013904223u; return (float(seed_value >> 8) / 16777216.f - .5f) * .2f; }

template<typename T> struct Network {
    int input, hidden, output;
    std::vector<T> w1,b1,w2,b2;
    Network(int i,int h,int o):input(i),hidden(h),output(o),w1(size_t(i)*h),b1(h),w2(size_t(h)*o),b2(o) {
        seed_value=123456789u;
        for(auto& x:w1)x=T(pseudo_random()); for(auto& x:b1)x=T(pseudo_random());
        for(auto& x:w2)x=T(pseudo_random()); for(auto& x:b2)x=T(pseudo_random());
    }
    T infer(const std::vector<T>& x, std::vector<T>& mid, std::vector<T>& y) const {
        for(int j=0;j<hidden;j++) {
            T v=b1[j]; for(int k=0;k<input;k++)v+=x[k]*w1[size_t(k)*hidden+j];
            mid[j]=std::max(T(0),v);
        }
        for(int j=0;j<output;j++) {
            T v=b2[j];for(int k=0;k<hidden;k++)v+=mid[k]*w2[size_t(k)*output+j];
            y[j]=v;
        }
        return y[0];
    }
    size_t model_bytes() const {return (w1.size()+b1.size()+w2.size()+b2.size())*sizeof(T);}
};

template<typename T> void run(std::ofstream& csv,int hidden,int iterations,int repeats) {
    Network<T> net(64,hidden,8);
    std::vector<T> x(64),mid(hidden),y(8);
    for(int i=0;i<64;i++)x[i]=T(i%11)/T(11);
    volatile T checksum=0;
    for(int k=0;k<500;k++)checksum=checksum+net.infer(x,mid,y);
    for(int r=1;r<=repeats;r++) {
        auto start=std::chrono::steady_clock::now();
        for(int k=0;k<iterations;k++)checksum=checksum+net.infer(x,mid,y);
        auto stop=std::chrono::steady_clock::now();
        double ms=std::chrono::duration<double,std::milli>(stop-start).count();
        double us=ms*1000.0/iterations;
        csv<<(std::is_same<T,float>::value?"float32":"float64")<<','<<hidden<<','<<r<<','<<iterations<<','<<std::fixed<<std::setprecision(6)<<us<<','<<net.model_bytes()<<'\n';
        std::cout<<(std::is_same<T,float>::value?"float32":"float64")<<" hidden="<<hidden<<" repeat="<<r<<" us/inference="<<us<<"\n";
    }
    if(checksum==T(-9999))std::cerr<<"unreachable\n";
}
int main(int argc,char** argv) {
    int iterations=10000,repeats=5;
    if(argc>1)iterations=std::stoi(argv[1]);
    if(argc>2)repeats=std::stoi(argv[2]);
    if(iterations<100||iterations>10000000||repeats<1||repeats>50){std::cerr<<"Usage: ./ai_benchmark [iterations 100..10000000] [repeats 1..50]\n";return 1;}
    std::ofstream csv("results.csv");
    if(!csv){std::cerr<<"Cannot write results.csv\n";return 1;}
    csv<<"precision,hidden_neurons,repeat,iterations,latency_us,model_bytes\n";
    for(int h:{32,128,512}){run<float>(csv,h,iterations,repeats);run<double>(csv,h,iterations,repeats);}
    std::cout<<"Saved results.csv. These are CPU inference timings, NOT power measurements or accuracy scores.\n";
}
