#!/usr/bin/python
import sys, locale
from optparse import OptionParser

class comm:                        
    def __init__(self, file1, file2):
        self.lines1 = []
        if file1 != '-':
            with open(file1) as f1:
                self.lines1 = f1.readlines()
            f1.close()
        else:   
            for line1 in sys.stdin:
                self.lines1.append(line1)
        self.lines1 = [x.strip() for x in self.lines1] 

        self.lines2 = []
        if file2 != '-':
            with open(file2) as f2:
                self.lines2 = f2.readlines()
            f2.close()
        else:
            for line2 in sys.stdin:
                self.lines2.append(line2)
        self.lines2 = [x.strip() for x in self.lines2]



    def isSorted(self):
        for i in range(0, len(self.lines1) - 1):
            if locale.strcoll(self.lines1[i], self.lines1[i + 1]) > 0:
                return False

        for i in range(0, len(self.lines2) - 1):
            if  locale.strcoll(self.lines2[i], self.lines2[i + 1]) > 0:
                return False

        return True


    def sortedOutput(self):
        i, j = 0, 0
        output = ''
        while i < len(self.lines1) and j < len(self.lines2):
            if locale.strcoll(self.lines1[i], self.lines2[j]) == 0:
                if self.sup3 == False:
                    if self.sup1 == True and self.sup2 == True:
                        output = output + self.lines1[i] + '\n'
                    elif self.sup1 == False and self.sup2 == False:
                        output = output + '\t\t' +self.lines1[i] + '\n'
                    else:
                        output = output + '\t' +self.lines1[i] + '\n'
                self.lines1 = self.lines1[1:]
                self.lines2 = self.lines2[1:]

            elif locale.strcoll(self.lines1[i], self.lines2[j]) < 0:
                if self.lines1[i] not in self.lines2:
                    if self.sup1 == False:       
                        output = output + self.lines1[i] + '\n'
                    self.lines1 = self.lines1[1:]

            elif locale.strcoll(self.lines1[i], self.lines2[j]) > 0:
                if self.lines2[j] not in self.lines1:
                    if self.sup2 == False:
                        if self.sup1 == False:
                            output = output +  '\t' + self.lines2[j] + '\n'
                        else:
                            output = output + self.lines2[j] + '\n'
                    self.lines2 = self.lines2[1:]

        if len(self.lines1) > 0:
            if self.sup1 == False:
                for line1 in self.lines1:
                    output = output + line1 + '\n'
        if len(self.lines2) > 0:
            if self.sup2 == False:
                if self.sup1 == False:
                    for line2 in self.lines2:
                        output = output + '\t' + line2 + '\n'
                else:
                    for line2 in self.lines2:
                        output = output + line2 + '\n'

        return output


    def unsortedOutput(self):
        output = ''
        tempLines2 = self.lines2

        for line1 in self.lines1:
            if line1 in tempLines2:
                if self.sup3 == False:
                    if self.sup1 == True and self.sup2 == True:
                        output = output + line1 + '\n'
                    elif self.sup1 == False and self.sup2 == False:
                        output = output + '\t\t' + line1 + '\n'
                    else:
                        output = output + '\t' + line1 + '\n'
                tempLines2.remove(line1)
            else:
                if self.sup1 == False:       
                    output = output + line1 + '\n'
                    
        for line2 in self.lines2:
            if line2 not in self.lines1:
                if self.sup2 == False:
                    if self.sup1 == False:
                       output = output +  '\t' + line2 + '\n'
                    else:
                        output = output + line2 + '\n'

        return output

    def setOptions(self, sup1, sup2, sup3, unsorted):
        self.sup1 = sup1
        self.sup2 = sup2
        self.sup3 = sup3
        self.unsorted = unsorted
    

def main():
    version_msg = "%prog 2.0"
    usage_msg = """%prog [-123u] file1 file2

    Select or reject lines common to two files."""

    parser = OptionParser(version=version_msg,
    usage=usage_msg)
    parser.add_option("-1", action="store_true", dest="sup1", default = False,
    help="Suppress the output column of lines unique to file1.")
    parser.add_option("-2", action="store_true", dest="sup2", default = False,
    help="Suppress the output column of lines unique to file2.")
    parser.add_option("-3", action="store_true", dest="sup3", default = False,
    help="Suppress the output column of lines duplicated in file1 and file2.")
    parser.add_option("-u", action="store_true", dest="unsorted", 
    default = False, help="Let comm work even if the inputs are not sorted.")

    options, args = parser.parse_args(sys.argv[1:])  

    if len(args) != 2:                                 
        parser.error("wrong number of operands")

    file1 = args[0]                               
    file2 = args[1]

    if file1 == '-' and file2 == '-':
        parser.error("You cannot input both files by standard input.")
        

    try:
        generator = comm(file1, file2)
        generator.setOptions(options.sup1, options.sup2, 
                            options.sup3, options.unsorted)
        if options.unsorted == False:
            if generator.isSorted() == False:
                parser.error("Files unsorted! You need to include -u option.")
            sys.stdout.write(generator.sortedOutput())
        else:
            sys.stdout.write(generator.unsortedOutput())
    except IOError as e:
        errno = e.errno
        strerror = e.strerror
        parser.error("I/O error({0}): {1}".
                      format(errno, strerror))

if __name__ == "__main__":
    main()