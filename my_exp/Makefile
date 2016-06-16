TRACE=trc_rt
ARP=arp

all: arp trace
arp:
	cd $(ARP);make arp;cd -
trace:
	cd $(TRACE);make trace;cd -

clean: clean_trace clean_arp


clean_trace:
	cd $(TRACE);make clean;cd -
clean_arp:
	cd $(ARP); make clean; cd -
