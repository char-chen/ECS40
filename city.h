#ifndef CITY_H
  #define CITY_H

class City
{
  double longitude;
  double latitude;
  char *name;
  char *state;
  char *airport;
  double population;

public:
  City();
  ~City();
  double getLong();
  void setLong(double val);
  double getLat();
  void setLat(double val);
  char* getName();
  void setName(char *n);
  char* getState();
  void setState(char *s);
  char* getAir();
  void setAir(char *a);
  double getPop();
  void setPop(double val);   
};
#endif
