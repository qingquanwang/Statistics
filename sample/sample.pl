#!/usr/local/bin/perl -w
use strict;
use Getopt::Long;
use POSIX;

sub weight_sample(){
	my ($k) = @_;
	my $line;
	my @item;
	my @weight;
	my @start;
	my $cnt = 0;
	my $each_item;
	my $each_weight;
	my $total=0;
	my $i;
	while($line = <STDIN>){
		chomp($line);
		($each_item,$each_weight) = split(//,$line);
		if($each_weight =~ /[0-9]+/){
			++$cnt;
			push(@item,$each_item);
			push(@weight,$each_weight);
	#		print "DEBUG:$each_weight\n";
		}
	}
	$total = scalar(@weight);
	my $sum=0;
	for($i=0;$i<$total;++$i){
		push(@start,$sum);
		$sum=$sum+$weight[$i];
	}
	push(@start,$sum);
	if($sum <= $k){
		for($i=0;$i<$total;++$i){
			print $item[$i],"\n";
		}
		return;
	}
	my $iter = int(rand(floor($sum/$k)));
	my $iter_begin = $iter;
	my @result;
	my $j=0;
	for($i=0;$i<$total;){
		if(($iter>$start[$i]) and ($iter<=$start[$i+1])){
			push(@result,$item[$i]);
			++$j;
	#		print "ITER:$iter\n";
			$iter = $iter_begin + floor($sum*$j/$k);
			if($j==$k){last;}
		}else{
			++$i;
		}
	}
	for($i=0;$i<$k;++$i){
		print $result[$i],"\n";
	}
}
sub sample(){
	my ($k) = @_;
	my $line;
	my $i=0;
	my @results;
	my $inside;
	while($line = <STDIN>){
		chomp $line;
		++$i;
		if($i<=$k){
			push(@results,$line);
		}else{
			$inside = rand($i);
			if($inside<$k){
				$results[$inside]=$line;
			}
		}
	}
	if($i<$k){
		$k=$i;
	}
	for($i=0;$i<$k;++$i){
		print $results[$i],"\n"; 
	}
}

my $k = 10;
my $weighted = 0;
my $result = GetOptions ("samples=i" => \$k,
					  "weighted=i"=> \$weighted);

if($weighted != 0){
	&weight_sample($k);
}else{
	&sample($k);
}

