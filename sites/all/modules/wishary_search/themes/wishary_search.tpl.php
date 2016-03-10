<div>
    <div class="search-results-loader"></div>
    <div class="search-results">
        <?php
            $search_results = module_invoke('wishary_search', 'block_view', 'search_results');
            print render($search_results['content']);
        ?>
    </div>
</div>
