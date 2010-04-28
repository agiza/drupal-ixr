<?php

/**
 * Fetches feeds using IXR XML-RPC library
 */
class IXRFeedsBatch extends FeedsImportBatch {
  protected $domain;
  protected $path;
  protected $service;

  public function __construct($url, $path, $service) {
    $this->url = $url;
    $this->path = $path;
    $this->service = $service;
    parent::__construct();
  }

  public function getRaw() {
    $client = ixr_create_clientssl($this->url, $this->path);
    $client->query($this->service);
    $response = $client->getResponse();
    return $response;
  }  
}

class IXRFeedsFetcher extends FeedsFetcher {
  public function fetch(FeedsSource $source) {
    $source_config = $source->getConfigFor($this);
    return new IXRFeedsBatch($source_config['server'], $source_config['path'], $source_config['service']);
  }

  public function sourceForm($source_config) {
    $form = array();
    // When renaming, do not forget feeds_vews_handler_field_source class.
    $form['server'] = array(
      '#type' => 'textfield',
      '#title' => t('Server name'),
      '#description' => t('Domain name of the XML-RPC server, i.e. webapp4-dev.asu.edu'),
      '#default_value' => isset($source_config['server']) ? $source_config['server'] : '',
    );
    $form['path'] = array(
      '#type' => 'textfield',
      '#title' => t('Path'),
      '#description' => t('Path to XML-RPC service on server.'),
      '#default_value' => isset($source_config['path']) ? $source_config['path'] : '',
    );
    $form['service'] = array(
      '#type' => 'textfield',
      '#title' => t('Service'),
      '#description' => t('Name of service to call.'),
      '#default_value' => isset($source_config['service']) ? $source_config['service'] : '',
    );
    return $form;
  }


}