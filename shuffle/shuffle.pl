#!/usr/local/bin/perl -w
use strict;
use Getopt::Long;
use POSIX;

my @results;
my $i=0;
my $line;
my $k;
while($line = <STDIN> ){
	chomp $line;
	push(@results,$line);
	$k = rand($i);
	$results[$i]=$results[$k];
	$results[$k]=$line;
	++$i;
}

for($k=0;$k<$i;++$k){
	print $results[$k]."\n";
}
