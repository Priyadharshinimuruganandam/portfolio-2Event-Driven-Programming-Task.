#include<iostream>
using namespace std;
class Sensor
{
  class State *current;
  public:
    Sensor();
    void setCurrent(State *s)
    {
        current = s;
    }

    void sensing();
    void processing();
};

class State
{
  public:
  virtual void idle(Sensor *sen)
    {
        cout << "  Idle\n";
    }
    virtual void sensing(Sensor *sen)
    {
        cout << "   Sensing Sensor\n";
    }
    virtual void processing(Sensor *sen)
    {
        cout << " Sensing sensor\n";
    }
};

void Sensor::sensing()
{
  current->sensing(this);
}

void Sensor::processing()
{
  current->processing(this);
}

class Sense: public State
{
    int temp, humidity;
  public:
    Sense()
    {
        cout << "   Sensing Temperature Sensor ";
        cout << "   Sensing Humidity Sensor ";
     int a=20;
                  for(a=0;a<30;a++)
                    {
                        cout << "The Temperature Sensor : " << temp <<endl;
                    }
     int b=40;
                 for(b=0;b<50;b++)
                    {
                        cout << "The Humidity Sensor : " << humidity <<endl;
                    }
    };
    ~Sense()
    {
        cout << "   Sensing in process \n";

    };
   // void processing(Sensor *sen);
};

class Process: public State
{
  public:
    Process()
    {
        cout << " Transfering data is in process ";
    };
    ~Process()
    {
        cout << "   Processing completed\n";
    };
    void sensing(Sensor *sen)
    {
        cout << "   Sensing state to processing State";
        sen->setCurrent(new Sense());
        delete this;
    }
};


void Sense::sensing(Sensor *sen)
{
  cout << "   sensing state to processing state";
  sen->setCurrent(new Process());
  delete this;
}

void Sense::processing(Sensor *sen)
{
  cout << "   Processing state to idle state";
  sen->setCurrent(new Process());
  delete this;
}

Sensor::Sense()
{
  current = new Process();
  cout << "Idle state" ;
}

int main()
{
  void(Sensor:: *ptrs[])() =
  {
    Sensor::processing, Sensor::sensing
  };
  Sensor fsm;
  int num;
  while (1)
  {
    cout << "Enter the state to be done:";
    cin >> num;
    (fsm.*ptrs[num])();
  }
}
