<?php

$plugin = array(
  'title' => 'Drupal node feed', 
  'description' => "Consume a feed produced by drupal's built in node_feed() function published at /rss.xml",
  'callback' => 'feedqueue_feed_type_node_feed', 
);

function feedqueue_feed_type_node_feed($feed_url) {
  $feed = file_get_contents($feed_url);
  if (!$feed) {
    return FALSE;
  }

  $doc = new DOMDocument();
  $doc->loadXML($feed);
  $xpath = new DOMXpath($doc);

  $nids = array();
  $elements = $xpath->query("//guid");
  if (!is_null($elements)) {
    foreach ($elements as $element) {
      $nids[] = intval($element->nodeValue);
    }
  }
  return $nids;
}
