import sys
reload(sys)
sys.setdefaultencoding('utf8')
import os

#test function  
def add(a,b):  
	return a + b 
  
class CallPy:
	def unicode2utf8(self, body):
		#print ("py: "+body);
		#print "py: "+body.decode('unicode-escape', 'ignore').encode('utf-8');
		return body.decode('unicode-escape', 'ignore').encode('utf-8');

if __name__ == '__main__':
	call = CallPy();
	print ("py: "+call.unicode2utf8('value=\"\u738b\u5b9d\u5f3a\"'));
	  
   
