<?php
if(isset($_POST["url"]))
{
    $get_url = $_POST["url"];
	$options = array('http' => array('header' => "User-Agent: myFooAgent\r\n"));
	$context = stream_context_create($options);
	$get_content = file_get_contents($get_url, false, $context);
	$get_content = preg_match_all('/<img[^>]+>/i',$get_content, $result);
	$output = array('images'=>$result[0]);
	$image_urls = array();
	for($i=0; $i<count($output['images']); $i++){
		$img_path = $output['images'][$i];
		libxml_use_internal_errors(true);
		$doc = new DOMDocument();
		$doc->loadHTML($img_path);
		$images = $doc->getElementsByTagName("img");
		foreach ($images as $key => $image){
			if ($image->hasAttribute("data-src")){
				$src = $image->getAttribute("data-src");
				$src = str_replace('%>','',$src);
				if (false === strpos($src, '://')) {
					$src = 'http:' . $src;
				}
				if(strlen($src) > 0){
					if (preg_match("@^[hf]tt?ps?://@", $src)) {
						if(exif_imagetype($src)) {
							if(!preg_match('/thumb-default/',$src)){
								$image_urls['images'][] = $src;
							}
						}
					}
				}
			}else if ($image->hasAttribute("src2")){
				$src = $image->getAttribute("src2");
				$src = str_replace('%>','',$src);
				if (false === strpos($src, '://')) {
					$src = 'http:' . $src;
				}
				if(strlen($src) > 0){
					if (preg_match("@^[hf]tt?ps?://@", $src)) {
						if(exif_imagetype($src)) {
							if(!preg_match('/thumb-default/',$src)){
								$image_urls['images'][] = $src;
							}
						}
					}
				}
				
			}else if ($image->hasAttribute("src")){
				$src = $image->getAttribute("src");
				$src = str_replace('%>','',$src);
				if (false === strpos($src, '://')) {
					$src = 'http:' . $src;
				}
				if(strlen($src) > 0){
					if (preg_match("@^[hf]tt?ps?://@", $src)) {
						if(exif_imagetype($src)) {
							if(!preg_match('/thumb-default/',$src)){
								$image_urls['images'][] = $src;
							}
						}
					}
				}
				
			}
		}

	}
	echo json_encode($image_urls);
}

?>