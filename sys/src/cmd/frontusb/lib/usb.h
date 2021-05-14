typedef struct Altc Altc;
typedef struct Conf Conf;
typedef struct DConf DConf;
typedef struct DDesc DDesc;
typedef struct DDev DDev;
typedef struct DEp DEp;
typedef struct DIface DIface;
typedef struct Desc Desc;
typedef struct Dev Dev;
typedef struct Ep Ep;
typedef struct Iface Iface;
typedef struct Usbdev Usbdev;

enum {
	/* fundamental constants */
	Nep	= 256,	/* max. endpoints per usb device & per interface */

	/* tunable parameters */
	Nconf	= 16,	/* max. configurations per usb device */
	Nddesc	= 8*Nep, /* max. device-specific descriptors per usb device */
	Niface	= 16,	/* max. interfaces per configuration */
	Naltc	= 256,	/* max. alt configurations per interface */
	Uctries	= 4,	/* no. of tries for usbcmd */
	Ucdelay	= 50,	/* delay before retrying */

	/* request type */
	Rh2d	= 0<<7,		/* host to device */
	Rd2h	= 1<<7,		/* device to host */ 

	Rstd	= 0<<5,		/* types */
	Rclass	= 1<<5,
	Rvendor	= 2<<5,

	Rdev	= 0,		/* recipients */
	Riface	= 1,
	Rep	= 2,		/* endpoint */
	Rother	= 3,

	/* standard requests (USB2.0) */
	Rgetstatus	= 0,
	Rclearfeature	= 1,
	Rsetfeature	= 3,
	Rsetaddress	= 5,
	Rgetdesc	= 6,
	Rsetdesc	= 7,
	Rgetconf	= 8,
	Rsetconf	= 9,
	Rgetiface	= 10,
	Rsetiface	= 11,
	Rsynchframe	= 12,

	/* standard requests (USB3.0) */
	Rsethubdepth	= 12,
	Rgetporterrcnt	= 13,

	Rgetcur	= 0x81,
	Rgetmin	= 0x82,
	Rgetmax	= 0x83,
	Rgetres	= 0x84,
	Rsetcur	= 0x01,
	Rsetmin	= 0x02,
	Rsetmax	= 0x03,
	Rsetres	= 0x04,

	/* dev classes */
	Clnone		= 0,		/* not in usb */
	Claudio		= 1,
	Clcomms		= 2,
	Clhid		= 3,
	Clprinter	= 7,
	Clstorage	= 8,
	Clhub		= 9,
	Cldata		= 10,

	/* standard descriptor sizes */
	Ddevlen		= 18,
	Dconflen	= 9,
	Difacelen	= 9,
	Deplen		= 7,

	/* descriptor types */
	Ddev		= 1,
	Dconf		= 2,
	Dstr		= 3,
	Diface		= 4,
	Dep		= 5,
	Dreport		= 0x22,
	Dfunction	= 0x24,
	Dphysical	= 0x23,

	/* feature selectors */
	Fdevremotewakeup = 1,
	Fhalt 	= 0,

	/* device state */
	Detached = 0,
	Attached,
	Enabled,
	Assigned,
	Configured,

	/* endpoint direction */
	Ein = 0,
	Eout,
	Eboth,

	/* endpoint type */
	Econtrol = 0,
	Eiso = 1,
	Ebulk = 2,
	Eintr = 3,

	/* endpoint isotype */
	Eunknown = 0,
	Easync = 1,
	Eadapt = 2,
	Esync = 3,

	/* endpoint isousage */
	Edata = 0,
	Efeedback = 1,
	Eimplicit = 2,

	/* config attrib */
	Cbuspowered = 1<<7,
	Cselfpowered = 1<<6,
	Cremotewakeup = 1<<5,

	/* report types */
	Tmtype	= 3<<2,
	Tmitem	= 0xF0,
	Tmain	= 0<<2,
		Tinput	= 0x80,
		Toutput	= 0x90,
		Tfeature = 0xB0,
		Tcoll	= 0xA0,
		Tecoll	= 0xC0,
	 Tglobal	= 1<<2,
		Tusagepage = 0x00,
		Tlmin	= 0x10,
		Tlmax	= 0x20,
		Tpmin	= 0x30,
		Tpmax	= 0x40,
		Tunitexp	= 0x50,
		Tunit	= 0x60,
		Trepsize	= 0x70,
		TrepID	= 0x80,
		Trepcount = 0x90,
		Tpush	= 0xA0,
		Tpop	= 0xB0,
	 Tlocal	= 2<<2,
		Tusage	= 0x00,
		Tumin	= 0x10,
		Tumax	= 0x20,
		Tdindex	= 0x30,
		Tdmin	= 0x40,
		Tdmax	= 0x50,
		Tsindex	= 0x70,
		Tsmin	= 0x80,
		Tsmax	= 0x90,
		Tsetdelim = 0xA0,
	 Treserved	= 3<<2,
	 Tlong	= 0xFE,

};

/*
 * Usb device (when used for ep0s) or endpoint.
 * RC: One ref because of existing, another one per ogoing I/O.
 * per-driver resources (including FS if any) are released by aux
 * once the last ref is gone. This may include other Devs using
 * to access endpoints for actual I/O.
 */
struct Dev
{
	Ref	ref;
	char*	dir;		/* path for the endpoint dir */
	int	id;		/* usb id for device or ep. number */
	int	dfd;		/* descriptor for the data file */
	int	cfd;		/* descriptor for the control file */
	int	isusb3;		/* this is a usb3 device */
	int	depth;		/* hub depth for usb3 hubs */
	int	maxpkt;		/* cached from usb description */
	Usbdev*	usb;		/* USB description */
	void*	aux;		/* for the device driver */
	char*	hname;		/* hash name, unique for device */
};

/*
 * device description as reported by USB (unpacked).
 */
struct Usbdev
{
	int	ver;		/* usb version */
	u32	csp;		/* USB class/subclass/proto */
	int	vid;		/* vendor id */
	int	did;		/* product (device) id */
	int	dno;		/* device release number */
	char*	vendor;
	char*	product;
	char*	serial;
	int	vsid;
	int	psid;
	int	ssid;
	int	class;		/* from descriptor */
	int	nconf;		/* from descriptor */
	Conf*	conf[Nconf];	/* configurations */
	Ep*	ep[Nep];	/* all endpoints in device */
	Desc*	ddesc[Nddesc];	/* (raw) device specific descriptors */
};

struct Ep
{
	u8	addr;		/* endpt address, 0-15 (|0x80 if Ein) */
	u8	dir;		/* direction, Ein/Eout */
	u8	type;		/* Econtrol, Eiso, Ebulk, Eintr */
	u8	isotype;	/* Eunknown, Easync, Eadapt, Esync */
	u8	isousage;	/* Edata, Efeedback, Eimplicit */
	
	int	id;
	int	maxpkt;		/* max. packet size */
	int	ntds;		/* nb. of Tds per µframe */
	Conf*	conf;		/* the endpoint belongs to */
	Iface*	iface;		/* the endpoint belongs to */
};

struct Altc
{
	int	attrib;
	int	interval;
	int	maxpkt;
	int	ntds;
	void*	aux;		/* for the driver program */
};

struct Iface
{
	int 	id;		/* interface number */
	u32	csp;		/* USB class/subclass/proto */
	Altc*	altc[Naltc];
	Ep*	ep[Nep];
	void*	aux;		/* for the driver program */
};

struct Conf
{
	int	cval;		/* value for set configuration */
	int	attrib;
	int	milliamps;	/* maximum power in this config. */
	Iface*	iface[Niface];
};

/*
 * Device-specific descriptors.
 * They show up mixed with other descriptors
 * within a configuration.
 * These are unknown to the library but handed to the driver.
 */
struct DDesc
{
	u8	bLength;
	u8	bDescriptorType;
	u8	bbytes[1];
	/* extra bytes allocated here to keep the rest of it */
};

struct Desc
{
	Conf*	conf;		/* where this descriptor was read */
	Iface*	iface;		/* last iface before desc in conf. */
	Ep*	ep;		/* last endpt before desc in conf. */
	Altc*	altc;		/* last alt.c. before desc in conf. */
	DDesc	data;		/* unparsed standard USB descriptor */
};

/*
 * layout of standard descriptor types
 */
struct DDev
{
	u8	bLength;
	u8	bDescriptorType;
	u8	bcdUSB[2];
	u8	bDevClass;
	u8	bDevSubClass;
	u8	bDevProtocol;
	u8	bMaxPacketSize0;
	u8	idVendor[2];
	u8	idProduct[2];
	u8	bcdDev[2];
	u8	iManufacturer;
	u8	iProduct;
	u8	iSerialNumber;
	u8	bNumConfigurations;
};

struct DConf
{
	u8	bLength;
	u8	bDescriptorType;
	u8	wTotalLength[2];
	u8	bNumInterfaces;
	u8	bConfigurationValue;
	u8	iConfiguration;
	u8	bmAttributes;
	u8	MaxPower;
};

struct DIface
{
	u8	bLength;
	u8	bDescriptorType;
	u8	bInterfaceNumber;
	u8	bAlternateSetting;
	u8	bNumEndpoints;
	u8	bInterfaceClass;
	u8	bInterfaceSubClass;
	u8	bInterfaceProtocol;
	u8	iInterface;
};

struct DEp
{
	u8	bLength;
	u8	bDescriptorType;
	u8	bEndpointAddress;
	u8	bmAttributes;
	u8	wMaxPacketSize[2];
	u8	bInterval;
};

#define Class(csp)	((csp) & 0xff)
#define Subclass(csp)	(((csp)>>8) & 0xff)
#define Proto(csp)	(((csp)>>16) & 0xff)
#define CSP(c, s, p)	((c) | (s)<<8 | (p)<<16)

#define	GET2(p)		(((p)[1] & 0xFF)<<8 | ((p)[0] & 0xFF))
#define	PUT2(p,v)	{(p)[0] = (v); (p)[1] = (v)>>8;}
#define	GET4(p)		(((p)[3]&0xFF)<<24 | ((p)[2]&0xFF)<<16 | \
			 ((p)[1]&0xFF)<<8  | ((p)[0]&0xFF))
#define	PUT4(p,v)	{(p)[0] = (v);     (p)[1] = (v)>>8; \
			 (p)[2] = (v)>>16; (p)[3] = (v)>>24;}

#define dprint if(usbdebug)fprint
#define ddprint if(usbdebug > 1)fprint

#pragma	varargck	type  "U"	Dev*
#pragma	varargck	argpos	devctl	2

int	Ufmt(Fmt *f);
char*	classname(int c);
void	closedev(Dev *d);
int	configdev(Dev *d);
int	devctl(Dev *dev, char *fmt, ...);
void*	emallocz(u32 size, int zero);
char*	estrdup(char *s);
char*	hexstr(void *a, int n);
int	loaddevconf(Dev *d, int n);
int	loaddevdesc(Dev *d);
char*	loaddevstr(Dev *d, int sid);
Dev*	opendev(char *fn);
int	opendevdata(Dev *d, int mode);
Dev*	openep(Dev *d, int id);
int	parseconf(Usbdev *d, Conf *c, u8 *b, int n);
int	parsedesc(Usbdev *d, Conf *c, u8 *b, int n);
int	parsedev(Dev *xd, u8 *b, int n);
int	unstall(Dev *dev, Dev *ep, int dir);
int	usbcmd(Dev *d, int type, int req, int value, int index, u8 *data,
		  int count);
Dev*	getdev(char *devid);

extern int usbdebug;	/* more messages for bigger values */

