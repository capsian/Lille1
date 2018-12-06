#ifndef TP_MBR_H
#define TP_MBR_H

#define MAX_VOL 8
#define MAGIC 0XCAFEBABE

enum vol_type_e {
  vol_base,
  vol_annexe,
  other
};

struct volume_s {

  int num_sec;
  int num_cyl;
  int nb_bloc;
  enum vol_type_e type;
};

struct mbr_s {

  struct volume_s vol[MAX_VOL];
  unsigned int nbVol;
  unsigned int magic;
};

extern struct mbr_s gMBR;

void save_mbr();
void load_mbr();

void ls_vol();
void ls_specific_vol(unsigned int vol);
void mkvol(unsigned int bSize, unsigned int cyl, unsigned int sec, unsigned int type);
void del_vol(unsigned int v);
void format_vol(unsigned int vol);

#endif
