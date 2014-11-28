<?php

require_once(dirname(__FILE__).'/mongo_reqcnt.class.php');
ini_set('date.timezone','Asia/Shanghai');
#error_reporting(E_ALL^E_NOTICE);

/*
type:
child - ������
main - ������
*/
$type = @$_GET['type'];
#$type = 'main';

/*
domain:����
*/
$domain = @$_GET['domain'];
#$domain = '@.eflypro.com';
if ($domain[0] == '@')
{
	$domain = substr($domain,2);
}


/*
timezone:
today - ����
month - ����
rweek - ���һ��
rmonth - ���һ��
rseason - ���һ��
rhalf - �������
ryear - ���һ��
*/
$timezone  = @$_GET['timezone'];
#$timezone = 'ryear';
   
/*
if (!isset($type) || !isset($domain) || !isset($timezone))
{
	echo "input error!\n";
	return;
}
*/

/*new class*/
$mongo = new MyMongo('121.201.12.60:22235');

if ($type == 'main')
{
	$domain = new MongoRegex("/$domain/");
}

switch($timezone)
{

case 'today':
	$data = $mongo->get_today_reqcnt($domain);
	break;

case 'month':
	$data = $mongo->get_month_reqcnt($domain);
	break;

case 'rweek':
	$data = $mongo->get_rweek_reqcnt($domain);
	break;
	
case 'rmonth':
	$data = $mongo->get_rmonth_reqcnt($domain);
	break;
	
case 'rseason':
	$data = $mongo->get_rseason_reqcnt($domain);
	break;
	
case 'rhalf':
	$data = $mongo->get_rhalf_reqcnt($domain);
	break;
	
case 'ryear':
	$data = $mongo->get_ryear_reqcnt($domain);
	break;
	
default:
	echo "wrong timezone!\n";
	print_r(json_encode(result_init('1','','')));
	exit();

}


print_r(json_encode(result_init('0','',$data)));

//END

function result_init($ret,$error,$data)
{
	$json_result = array();
	$json_result['ret'] = $ret;
	$json_result['error'] = $error;
	$json_result['descmap'] = $data;
	
	return $json_result;
	
}

?>