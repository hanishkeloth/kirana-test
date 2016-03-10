Request statistics for visitor and page.

The current documentation is at:
https://www.drupal.org/sandbox/peter/2484353

SEO, presentation, themes, they all depend on an understanding of who visits
your site and what they use to view your site. This module gives you a look
at what they use to view your site.


SEO

Site owners and developers dive into complicated approaches to presenting sites
on different browsers and multiple device formats without knowing exactly what
is used on their site. SEO can suffer due to overly complex changes.

Google now tests sites for responsive design. Responsive design is now one of
the top three SEO priorities.


Responsive design

One critical bit of information for responsive design is the width of the
devices used to view your site and the width of the window used on larger
screens. This package records and reports the width so you can focus on the
requirements of your visitors.


Width, height, user agent

This package records what is used on your site, the height, width, and user
agent. When the user resizes the window, you see the final size.

The information helps you make decisions about the resources you pour into your
responsive design. Do you provide multiple image sizes to provide maximum image
clarity while minimising download overheads? Yes, it is best practice. Now you
can see the actual window sizes used to view your site and optimize the images
with the minimum number of breaks.


Requirements

The reporting module requires views. There are no other requirements.

Installation

The three modules in the package are just standard Drupal add-on mudules
installed in the normal way. You switch on the base Request statistics module
first to create the database tables.

Switch the Request statistics record module on when you are ready to record
then switch the module off.

Switch on the Request statistics view module to see the reports.

Sample then report

The recording module is separate to the reporting module. You can switch
recording on and off at any time then analyse the records forever. When you
have enough data, you disable the recording module and use the view module to
present the data in Views.

All recording systems slow down your site. You can see the long wait for Google
analytics at the end of a page. Many of the statistics packages have the
problem that you have to leave the recording overhead switched on while
analysing the data.

We make life easier by separating data storage for recording. You switch the
recording on for an hour or a day then switch the recording off. The data
remains in the database with you analyse the information.


Data

There are two tables recording data. The Visitors table records the user id
when the visitor is a logged in user. The Requests table records page and other
requests. The two are linked for logged in users.

The Requests table records by year, month, day, and hour so you can analyse
usage across the day and across the week plus include longer term trends.

You get inner height and width to look at what size display you can really use.
You get outer height and width to see what is available when you can avoid
scroll bars. You get the screen height and width to see what is potentially
available if you could encourage people to expand their browser window.

The user agent string is included to give you an idea of the range of visitors
plus the robots and everything else hitting your Web site. The user agent
string is summarised as browser type, a virtual column containing desktop,
mobile, or tablet.


Views

All the data is available in Views ready for your custom reports. The included
reports are all views that you can clone to quick start your reports.

Views is included in Drupal 8 core so you might as well use it for everything
in Drupal 7. The data appears as a standard table in Views with relationships
to the user for page requests from logged in users. You could report almost
anything. You might produce separate report for visits by users testing new
devices.


Modules

This package contains three modules.
Request statistics
Request statistics record
Request statistics view


Request statistics

This is the base module required by the other two modules. This module creates
the tables to store the data. Install this module when you want to start
recording. Uninstall this module when you are finished reporting and want to
throw away the data.


Request statistics record

Install this module, Request statistics record, when you want to start
recording. Switch the module off to stop recoding and to stop the small
overhead produced by the recording.

The data will remain available for viewing after you uninstall Request
statistics record because the data is stored by Request statistics.


Request statistics view

Switch Request statistics view on to list the data through Views. This module
includes default views to list every table, column, and row. You can add you
own views for extra detail analysis.

You can contribute your views to this package by exporting the view and
attaching the export to an issue.


Security

The recording Ajax URL is the only opening for an attacker and is only open
when you record a sample of visitors. The URL could let an attacker insert
extra rows in your database. Remember to switch off the record module when you
finish recording your sample.


Testing

The modules are in production use at three sites. The supplied views created
some confusion.

The views included in the Request statistics view module can be cloned to
produce your own reports. You can also modify the supplied views but then the
module cannot delete or replace the supplied views, you have to remove the
modified views manually. Cloning is better than direct modification.

After you install, update, or replace Request statistics view, clear the cache
to see the menu entries and the views.
