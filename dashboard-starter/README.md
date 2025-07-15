# Dashboard Starter - Analytics Dashboard

A comprehensive analytics dashboard built with Fern UI Framework. This template demonstrates data visualization and dashboard development concepts including:

## Features

- **Metric Cards**: Key performance indicators with change indicators
- **Data Visualization**: Bar charts and pie charts for data representation
- **Real-time Updates**: Dynamic data display and updates
- **Responsive Layout**: Clean, organized dashboard layout
- **Activity Feed**: Recent activity and events display

## Dashboard Components

- **Header**: Branded dashboard header with title
- **KPI Cards**: Active users, revenue, orders, conversion rates
- **Traffic Sources**: Pie chart showing desktop/mobile/tablet traffic
- **Bar Chart**: Visual representation of traffic source percentages
- **Legend**: Color-coded data labels
- **Activity Feed**: Recent system events and actions

## Data Display

- **Active Users**: 2,547 (+12%)
- **Revenue**: $45,230 (+8%)
- **Orders**: 1,234 (+15%)
- **Conversion Rate**: 3.2% (-2%)

## Getting Started

```bash
cd dashboard-starter
fern fire                 # Run the dashboard
fern prepare web          # Build for web
fern prepare linux        # Build for Linux
```

## Code Structure

- `MetricCard` struct for KPI display
- `ChartData` struct for visualization data
- `drawMetricCard()` function for metric rendering
- `drawPieChart()` and `drawBarChart()` for data visualization
- `drawLegend()` for chart explanations
- Sample data structures for demonstration

## Customization Ideas

- Connect to real data sources and APIs
- Add interactive charts and filtering
- Implement date range selection
- Add export functionality (PDF, CSV)
- Create user role-based access
- Add real-time data updates
- Implement alert systems for thresholds

This template provides a solid foundation for building business dashboards with Fern!
